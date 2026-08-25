[README.md](https://github.com/user-attachments/files/31406695/README.md)# Shadow Network - Automatic Waste Management System

## Overview
This project is a QR code-based waste management system that uses liquid glass aesthetics for an attractive user interface. Users can login with a 6-digit password and earn points for recycling waste.

## Features
- **QR Code Generation**: Automatically generates a QR code that points to the web server
- **Liquid Glass Aesthetics**: Beautiful animated background with glass-morphism design
- **User Authentication**: 6-digit password-based login system
- **Points System**: Earn 5 points for each recycling action with beautiful animations
- **Team Branding**: Displays "Shadow Network" team name and "Vivek VM" as admin

## Project Structure
```
waste_bin_project/
├── app.py              # Main Python application
├── qr_code.png         # Generated QR code (created on first run)
├── password.txt        # Contains the generated 6-digit password
├── templates/
│   ├── index.html      # Login page with liquid glass design
│   └── dashboard.html  # User dashboard with points system
└── static/             # Static files (if needed)
```

## Installation

### Requirements
- Python 3.x
- Flask
- qrcode
- Pillow

### Install Dependencies
```bash
pip install flask qrcode pillow
```

## Usage

### Running the Application
```bash
cd /workspace/waste_bin_project
python app.py
```

### What Happens When You Run:
1. A random 6-digit password is generated
2. The password is saved to `password.txt`
3. A QR code (`qr_code.png`) is generated pointing to the web server
4. The web server starts on port 5000
5. Your default browser opens automatically to the website

### Accessing the Website
- **Scan the QR code**: Use any QR code scanner to access the website
- **Direct access**: Open `http://localhost:5000` in your browser
- **Network access**: The server is accessible from other devices on the same network

### Login Process
1. Enter any username
2. Enter the 6-digit password (found in `password.txt` or displayed in console)
3. Click "Login"

### Earning Points
1. After logging in, you'll see your dashboard
2. Click "Recycle & Earn 5 Points" button
3. Watch the beautiful animation with confetti and stars
4. Your points total will update

## Password Information
- The password is randomly generated each time you run the application
- It's a 6-digit number (e.g., 818263)
- Found in:
  - Console output when starting the server
  - `password.txt` file
  - Same for all users (system-wide password)

## Team Information
- **Team Name**: Shadow Network
- **Admin/Leader**: Vivek VM
- **Project**: Automatic Waste Management System using Google Teachable Machine

## Technical Details

### Backend (Flask)
- User session management
- Password validation
- Points tracking
- RESTful API endpoints

### Frontend
- Liquid glass background with animated blobs
- Glass-morphism card design
- Responsive layout
- Smooth animations for points earning
- Confetti and star effects

### QR Code
- Generated using the `qrcode` library
- Points to the local web server URL
- Automatically opened in browser

## API Endpoints

| Endpoint | Method | Description |
|----------|--------|-------------|
| `/` | GET | Login page |
| `/login` | POST | User authentication |
| `/dashboard` | GET | User dashboard |
| `/add_points` | POST | Add 5 points to user account |
| `/logout` | GET | Logout user |

## Customization

### Changing the Port
Edit `app.py` and change the `port` variable:
```python
port = 5000  # Change to desired port
```

### Modifying Points Value
Edit the `add_points()` function in `app.py`:
```python
points_to_add = 5  # Change to desired points value
```

## Troubleshooting

### Port Already in Use
If port 5000 is already in use, either:
1. Stop the existing process: `pkill -f "python app.py"`
2. Change the port in `app.py`

### QR Code Not Scanning
- Ensure the QR code image is clear
- Make sure your device is on the same network
- Try accessing the URL directly

### Browser Doesn't Open
- Manually open the URL shown in the console
- Check if your default browser is properly configured

## License
This project is created for Shadow Network's waste management initiative.

---
**Created by**: Vivek VM  
**Team**: Shadow Network  
**Purpose**: Automatic Waste Classification and Management

