This project is an IoT-based Smart Parking System that uses RFID technology, ESP32 microcontroller, and Firebase Cloud to automate vehicle access and parking management.

Each vehicle is identified using an RFID tag, and access is controlled in real time through a cloud-based database.

The system demonstrates Smart City concepts by combining:

IoT (ESP32 + RFID)
Cloud Computing (Firebase)
Embedded Systems
Real-time Access Control
🎯 Key Features
RFID-based vehicle authentication
Real-time access control (entry/exit)
Cloud database integration (Firebase Realtime DB)
Automatic gate decision (ALLOW / DENY)
Logging of all vehicle entries
Scalable smart parking architecture
ESP32-based communication system
🧠 System Architecture
RFID Tag → ESP32 → Firebase Cloud → Decision System → Gate Control
⚙️ Hardware Requirements
ESP32 Development Board
RFID RC522 Module
Servo Motor (Gate barrier)
IR Sensors (optional for slots)
Breadboard + Jumper wires
Power supply
💻 Software Requirements
Arduino IDE
Firebase Account
VS Code (optional for web dashboard)
Google Chrome
🔌 Pin Configuration (ESP32 ↔ RFID RC522)
RFID Pin	ESP32 Pin
SDA	GPIO 5
SCK	GPIO 18
MOSI	GPIO 23
MISO	GPIO 19
RST	GPIO 22
VCC	3.3V
GND	GND
☁️ Firebase Database Structure
rfid_users/
   UID_XXXX:
      name: "User Name"
      vehicle: "Vehicle Number"
      status: "active"

gate_logs/
   log_id:
      uid: "UID_XXXX"
      action: "entry"
      timestamp: 123456789
🔄 System Workflow
User scans RFID card at entrance
ESP32 reads UID from RFID
UID is sent to Firebase
System checks user validity
If valid → Gate opens
If invalid → Access denied
Entry is logged in Firebase
🚀 Technologies Used
ESP32
RFID RC522
Firebase Realtime Database
C++ (Arduino IDE)
IoT Architecture
📡 Features Explained
🔐 Authentication System

Each RFID card is linked to a registered user stored in Firebase.

☁️ Cloud Integration

All access decisions are validated through Firebase in real time.

🚧 Smart Gate Control

The system can trigger:

Servo motor (gate open/close)
LED indicators
Buzzer alerts
📊 Logging System

Every entry/exit is stored for monitoring and analytics.

📈 Future Improvements
Mobile app for parking management
QR code + RFID hybrid system
AI-based vehicle recognition (camera + YOLO)
Payment gateway integration
Multi-parking site support
Slot prediction using Machine Learning
🧪 Project Use Cases
Smart Cities
Universities parking systems
Corporate buildings
Industrial parking automation
Research IoT projects
👨‍💻 Author

Abdallah Ben Aicha
Electromechanical Engineering Student
IoT | AI | Embedded Systems | Smart Automation

📜 License

This project is intended for educational and academic purposes only.
