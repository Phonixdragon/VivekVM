# Shadow Network - Waste Management System

## 🌟 Features

### Dark Theme Design
- Modern dark aesthetic with liquid glass effects
- Animated background blobs with smooth transitions
- Professional cyan/blue color scheme

### Arc-Style Intro Animation
- Browser-like circular expansion animation on page load
- Smooth logo reveal with fade effects
- Professional entrance experience

### User Authentication
- 6-digit random password generated on each server start
- Password displayed prominently on login screen
- User registration and login system
- Session management

### Waste Disposal System
- Beautiful modal interface for waste disposal
- Counter to select number of items (1-10 limit)
- Real-time points preview (5 points per item)
- Smooth confirmation flow

### Points & Rewards
- Earn 5 points for each waste item disposed
- Large, animated points display
- "Claim Rewards" button to redeem points
- Smooth claiming animation with confetti effects

### Animations
- Success overlay with checkmark icon
- Colorful confetti celebration
- Toast notifications
- Smooth transitions throughout

## 🚀 How to Run

1. Navigate to the project directory:
```bash
cd waste_bin_project
```

2. Install dependencies (if not already installed):
```bash
pip install flask qrcode[pil]
```

3. Run the application:
```bash
python app.py
```

4. The application will:
   - Generate a random 6-digit password
   - Create a QR code (`qr_code.png`)
   - Save the password to `password.txt`
   - Start the web server on port 5000
   - Automatically open your default browser

## 📱 Accessing the Website

- **Local Access**: http://127.0.0.1:5000
- **Network Access**: http://[YOUR_IP]:5000
- **QR Code**: Scan `qr_code.png` with any QR scanner

## 🔐 Login Credentials

- **Username**: Choose any username (new users are auto-created)
- **Password**: Displayed on the login screen (changes each restart)

## 👥 Team

- **Admin/Leader**: Vivek VM
- **Team**: Shadow Network

## 🎨 Design Highlights

- Dark theme (#0a0a0f background)
- Cyan/blue gradient accents (#00d9ff, #0066ff)
- Glassmorphism effects
- Smooth animations and transitions
- Responsive design for all devices

## 📁 Project Structure

```
waste_bin_project/
├── app.py                 # Main Flask application
├── templates/
│   ├── index.html        # Login page with intro animation
│   └── dashboard.html    # User dashboard with points system
├── static/               # Static files (if needed)
├── qr_code.png          # Generated QR code
├── password.txt         # Password reference file
└── README.md            # This file
```

## 🎯 Usage Flow

1. **Login**: Enter username and the displayed 6-digit password
2. **Dispose Waste**: Click "Dispose Waste" button
3. **Select Count**: Use +/- buttons to choose number of items (max 10)
4. **Confirm**: Click "Confirm" to earn points (5 points × count)
5. **View Points**: Watch your points accumulate with animations
6. **Claim Rewards**: Click "Claim Rewards" when ready to redeem

## 💡 Tips

- Maximum 10 items can be disposed at once
- Points reset after claiming rewards
- Password changes every time the server restarts
- QR code points to your local network IP for mobile access

---

**Shadow Network** - Making waste management rewarding! ♻️
