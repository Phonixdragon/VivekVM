#!/usr/bin/env python3
"""
Shadow Network - Waste Bin QR Code Generator and Web Server
Admin: Vivek VM
Dark theme with Arc-style intro animation, waste disposal counter, and rewards system.
"""

import qrcode
import random
import os
import threading
import webbrowser
from flask import Flask, render_template, request, jsonify, session, redirect, url_for

# Configuration
app = Flask(__name__)
app.secret_key = os.urandom(24)

# Generate a random 6-digit password
PASSWORD = str(random.randint(100000, 999999))
print(f"\n{'='*50}")
print(f"SHADOW NETWORK - Waste Bin System")
print(f"{'='*50}")
print(f"Admin: Vivek VM")
print(f"Generated 6-Digit Password: {PASSWORD}")
print(f"{'='*50}\n")

# User database (in-memory for demo)
users_db = {
    'vivek': {'password': PASSWORD, 'points': 0, 'is_admin': True}
}

# Store the password in a file for reference
with open('password.txt', 'w') as f:
    f.write(f"Shadow Network - Waste Bin System\n")
    f.write(f"Admin: Vivek VM\n")
    f.write(f"6-Digit Password: {PASSWORD}\n")
    f.write(f"\nKeep this password safe!\n")

def generate_qr_code(url, filename='qr_code.png'):
    """Generate a QR code for the given URL"""
    qr = qrcode.QRCode(
        version=1,
        error_correction=qrcode.constants.ERROR_CORRECT_L,
        box_size=10,
        border=4,
    )
    qr.add_data(url)
    qr.make(fit=True)
    
    img = qr.make_image(fill_color="#00d9ff", back_color="#0a0a0f")
    img.save(filename)
    print(f"QR Code generated: {filename}")
    return filename

@app.route('/')
def index():
    """Main page with login form"""
    if 'logged_in' in session and session['logged_in']:
        return redirect(url_for('dashboard'))
    return render_template('index.html', password=PASSWORD)

@app.route('/login', methods=['POST'])
def login():
    """Handle login request"""
    username = request.form.get('username', '').strip()
    password = request.form.get('password', '').strip()
    
    # Check if user exists or create new user
    if username in users_db:
        if users_db[username]['password'] == password:
            session['logged_in'] = True
            session['username'] = username
            session['points'] = users_db[username]['points']
            session['is_admin'] = users_db[username].get('is_admin', False)
            return jsonify({'success': True, 'message': 'Login successful!'})
        else:
            return jsonify({'success': False, 'message': 'Incorrect password!'})
    else:
        # Create new user with the system password
        if password == PASSWORD:
            users_db[username] = {'password': password, 'points': 0, 'is_admin': False}
            session['logged_in'] = True
            session['username'] = username
            session['points'] = 0
            session['is_admin'] = False
            return jsonify({'success': True, 'message': 'Account created and logged in!'})
        else:
            return jsonify({'success': False, 'message': 'Invalid password!'})

@app.route('/dashboard')
def dashboard():
    """User dashboard with points"""
    if 'logged_in' not in session or not session['logged_in']:
        return redirect(url_for('index'))
    return render_template('dashboard.html', 
                         username=session['username'], 
                         points=session['points'],
                         is_admin=session.get('is_admin', False))

@app.route('/add_points', methods=['POST'])
def add_points():
    """Add points to user account based on waste count"""
    if 'logged_in' not in session or not session['logged_in']:
        return jsonify({'success': False, 'message': 'Not logged in'})
    
    data = request.get_json()
    count = int(data.get('count', 1))
    
    # Limit between 1 and 10 items per disposal
    if count < 1:
        count = 1
    elif count > 10:
        count = 10
    
    points_to_add = count * 5
    
    users_db[session['username']]['points'] += points_to_add
    session['points'] = users_db[session['username']]['points']
    
    return jsonify({
        'success': True, 
        'message': f'Congratulations! You earned {points_to_add} points!',
        'new_points': session['points'],
        'points_earned': points_to_add
    })

@app.route('/claim_rewards', methods=['POST'])
def claim_rewards():
    """Claim all accumulated points"""
    if 'logged_in' not in session or not session['logged_in']:
        return jsonify({'success': False, 'message': 'Not logged in'})
    
    current_points = users_db[session['username']]['points']
    
    if current_points <= 0:
        return jsonify({'success': False, 'message': 'No points to claim!'})
    
    # Reset points after claiming
    users_db[session['username']]['points'] = 0
    session['points'] = 0
    
    return jsonify({
        'success': True, 
        'message': f'Successfully claimed {current_points} points!',
        'claimed_amount': current_points
    })

@app.route('/logout')
def logout():
    """Logout user"""
    session.clear()
    return redirect(url_for('index'))

if __name__ == '__main__':
    # Get the local IP address for network access
    import socket
    s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    try:
        s.connect(('8.8.8.8', 80))
        host_ip = s.getsockname()[0]
    except:
        host_ip = '127.0.0.1'
    finally:
        s.close()
    
    port = 8000
    url = f"http://{host_ip}:{port}"
    
    # Generate QR code
    qr_file = generate_qr_code(url)
    
    print(f"\nStarting web server at: {url}")
    print(f"Scan the QR code ({qr_file}) to access the website")
    print(f"Press Ctrl+C to stop the server\n")
    
    # Open browser after a short delay
    def open_browser():
        import time
        time.sleep(2)
        webbrowser.open(url)
    
    threading.Thread(target=open_browser, daemon=True).start()
    
    # Run the Flask app
    app.run(host='0.0.0.0', port=port, debug=False)
