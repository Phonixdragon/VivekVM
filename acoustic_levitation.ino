/*
 * Acoustic Levitation Controller
 * 
 * This code controls 40kHz ultrasonic transducers for acoustic levitation
 * using an Arduino Uno R3 and L298 Motor Driver Board.
 * 
 * Hardware Setup:
 * - Arduino Uno R3
 * - L298 Motor Driver Board
 * - 40kHz Ultrasonic Transducers (paired for standing wave creation)
 * 
 * Connections:
 * L298 to Arduino:
 * - IN1 -> Pin 9 (PWM)
 * - IN2 -> Pin 10 (PWM)
 * - IN3 -> Pin 5 (PWM)
 * - IN4 -> Pin 6 (PWM)
 * - ENA -> Pin 3 (PWM, speed control for transducer 1)
 * - ENB -> Pin 11 (PWM, speed control for transducer 2)
 * - VCC -> 12V (for transducers)
 * - GND -> GND (common ground with Arduino)
 * 
 * Transducers:
 * - Connect transducer 1 to OUT1 and OUT2
 * - Connect transducer 2 to OUT3 and OUT4
 * 
 * Note: For 40kHz operation, we use Timer1 to generate precise frequency
 */

// Pin definitions
#define IN1 9
#define IN2 10
#define IN3 5
#define IN4 6
#define ENA 3
#define ENB 11

// Frequency settings
#define TARGET_FREQUENCY 40000  // 40 kHz target frequency
#define TIMER1_PRESCALER 1      // No prescaling for maximum resolution

// Levitation parameters
int powerLevel = 128;           // PWM duty cycle (0-255), start at 50%
bool levitationActive = false;
unsigned long lastAdjustmentTime = 0;
const unsigned long adjustmentInterval = 100; // ms between adjustments

// Optional: Add button for manual control
#define BUTTON_PIN 2            // Interrupt pin for start/stop
#define POTENTIOMETER_PIN A0    // For manual power adjustment
#define LED_PIN 13              // Status indicator

volatile bool buttonPressed = false;

void setup() {
  // Initialize pins
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  
  // Attach interrupt for button
  attachInterrupt(digitalPinToInterrupt(BUTTON_PIN), buttonISR, FALLING);
  
  // Initialize serial communication
  Serial.begin(9600);
  Serial.println("Acoustic Levitation Controller Initialized");
  Serial.println("Frequency: 40 kHz");
  Serial.println("Press button on pin 2 to toggle levitation");
  
  // Configure Timer1 for 40kHz PWM
  setupTimer1();
  
  // Start with transducers off
  stopLevitation();
}

void loop() {
  // Check for button press
  if (buttonPressed) {
    buttonPressed = false;
    toggleLevitation();
    delay(50); // Debounce delay
  }
  
  // Read potentiometer for power adjustment if active
  if (levitationActive) {
    int potValue = analogRead(POTENTIOMETER_PIN);
    powerLevel = map(potValue, 0, 1023, 50, 255); // Limit range for safety
    
    // Apply power level
    analogWrite(ENA, powerLevel);
    analogWrite(ENB, powerLevel);
    
    // Periodic status update
    if (millis() - lastAdjustmentTime > adjustmentInterval) {
      lastAdjustmentTime = millis();
      Serial.print("Power Level: ");
      Serial.println(powerLevel);
    }
  }
  
  // Small delay to prevent overwhelming the loop
  delay(10);
}

// Button interrupt service routine
void buttonISR() {
  buttonPressed = true;
}

// Toggle levitation on/off
void toggleLevitation() {
  if (levitationActive) {
    stopLevitation();
  } else {
    startLevitation();
  }
}

// Start acoustic levitation
void startLevitation() {
  levitationActive = true;
  digitalWrite(LED_PIN, HIGH);
  
  // Set up phase relationship for standing wave
  // Transducer 1
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  
  // Transducer 2 (180 degrees out of phase for standing wave)
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  
  // Gradually ramp up power to avoid shock
  for (int i = 0; i <= powerLevel; i += 5) {
    analogWrite(ENA, i);
    analogWrite(ENB, i);
    delay(10);
  }
  
  Serial.println("Levitation STARTED");
  Serial.print("Operating Power: ");
  Serial.println(powerLevel);
}

// Stop acoustic levitation
void stopLevitation() {
  // Gradually ramp down power
  for (int i = powerLevel; i >= 0; i -= 5) {
    analogWrite(ENA, i);
    analogWrite(ENB, i);
    delay(10);
  }
  
  // Disable outputs
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  analogWrite(ENA, 0);
  analogWrite(ENB, 0);
  
  levitationActive = false;
  digitalWrite(LED_PIN, LOW);
  
  Serial.println("Levitation STOPPED");
}

// Configure Timer1 for 40kHz operation
void setupTimer1() {
  // Stop Timer1
  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1 = 0;
  
  // Set prescaler to 1 (no division)
  // Timer clock = 16MHz / 1 = 16MHz
  // Each tick = 62.5ns
  
  // For 40kHz, we need period = 1/40000 = 25 microseconds
  // With 16MHz clock and prescaler 1:
  // OCR1A = (16000000 / 40000) - 1 = 399
  
  OCR1A = 399;  // Compare value for 40kHz
  OCR1B = 199;  // 50% duty cycle (can be adjusted)
  
  // Set CTC mode (Clear Timer on Compare Match)
  TCCR1B |= (1 << WGM12);
  TCCR1A |= (1 << WGM11);
  
  // Set non-inverting output on OC1A (Pin 9)
  TCCR1A |= (1 << COM1A1);
  
  // Start timer with no prescaling
  TCCR1B |= (1 << CS10);
  
  // Enable output compare match interrupt (optional, for fine tuning)
  // TIMSK1 |= (1 << OCIE1A);
  
  Serial.println("Timer1 configured for 40kHz");
}

// Optional: Fine-tune frequency if needed
void adjustFrequency(int offset) {
  OCR1A = 399 + offset;
  Serial.print("Adjusted OCR1A: ");
  Serial.println(OCR1A);
  Serial.print("Actual Frequency: ");
  float actualFreq = 16000000.0 / (OCR1A + 1);
  Serial.print(actualFreq);
  Serial.println(" Hz");
}

// Safety function to check temperature/time limits
void safetyCheck() {
  static unsigned long startTime = 0;
  const unsigned long maxRunTime = 300000; // 5 minutes max continuous run
  
  if (levitationActive) {
    if (startTime == 0) {
      startTime = millis();
    }
    
    if (millis() - startTime > maxRunTime) {
      Serial.println("SAFETY: Maximum runtime reached, shutting down");
      stopLevitation();
      startTime = 0;
    }
  } else {
    startTime = 0;
  }
}
