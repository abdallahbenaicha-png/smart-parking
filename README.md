🚗 Smart Parking System using ESP32 and Firebase

This project is an IoT-based Smart Parking System that uses an ESP32 microcontroller, IR sensors, and Firebase Realtime Database to monitor parking slot availability in real time.

The system reads data from IR sensors installed in each parking slot to detect whether a slot is occupied or free. The ESP32 processes this data and sends updates to Firebase Cloud, enabling real-time synchronization with any connected web or mobile application.

To optimize performance and reduce network usage, the system only sends data to Firebase when a change in slot status is detected.

⚙️ Key Features
Real-time parking slot monitoring
IR sensor-based vehicle detection
ESP32 WiFi connectivity
Firebase Realtime Database integration
Optimized data transmission (only on state change)
Scalable smart parking architecture
🔄 System Workflow

IR Sensors → ESP32 → Firebase Cloud → Dashboard / Application

📊 Functionality
Slot value 0 = Free
Slot value 1 = Occupied
Automatic update of parking status in real time
Efficient cloud communication with minimal latency
🚀 Purpose

The goal of this project is to provide a smart and automated parking management system that improves efficiency, reduces manual monitoring, and demonstrates IoT integration with cloud computing.
