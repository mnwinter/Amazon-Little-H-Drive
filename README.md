# Lil H Drive Robot  ***STILL IN DEVELOPMENT FILES ARE STILL CHANGING***

<img width="3041" height="2268" alt="image" src="https://github.com/user-attachments/assets/6ae87de0-cb3b-4bcb-98d0-5bb4928abfdb" />

A compact autonomous/RC robot inspired by **Amazon Drive Units**, featuring a scissor-lift mechanism, N20 motors, and an **ESP32-S3 DevKit-C** microcontroller with Wi-Fi control and future BLE expansion.

This repository documents the hardware, electronics, firmware, and interface used to design and build the robot.

---

## 📦 Bill of Materials (BOM)

### 🔹 Motors & Wheels
- N20 DC Gear Motor, Magnetic Hall Encoder, All-Metal Gearbox, High Precision Reduction Motor, with L-Shaped 6PIN Connector
- Threaded Shaft M4 55mm DC Gear Motor 3V 6V 12V Mini Electric Screw Reducer N20 All Metal Gears Motor (1, 12V 1000rpm) 
- RecDec 4 Pack Mini Micro N20 Gear Motor Wheels (3 mm D-hole rubber tires) – Amazon  


### 🔹 Motor Drivers
- WWZMDiB DRV8833 1.5 A Dual H-Bridge Motor Driver Boards (6 pcs pack) – Amazon  

### 🔹 Microcontroller & Electronics
- ESP32-S3 DevKit-C (N16R8 module, Wi-Fi + BLE, GPIO 48 RGB status LED)   
- LM2596 buck converter for 10 V and 5 V rails  
- WS2812 RGB LED (optional status feedback)  
- ToF (Laser Distance) sensor – front obstacle detection
- Rechargeable 12V 2600mAh Lithium ion Battery Pack with Charger

---

## 📚 Documentation & References
- [ESP32-S3 Datasheet (PDF)](https://www.espressif.com/sites/default/files/documentation/esp32-s3_datasheet_en.pdf)  
- [ESP32 Arduino Core on GitHub](https://github.com/espressif/arduino-esp32)  
- [DRV8833 Motor Driver Datasheet (TI)](https://www.ti.com/lit/ds/symlink/drv8833.pdf)  
- [Adafruit N20 Gear Motor Guide](https://learn.adafruit.com/adafruit-micro-metal-gearmotor-encoders)  
- [Global Robotics University](https://globalroboticsuniversity.com)  

---

## ⚙️ Features
- Dual N20 gear motors for drive (left / right / strafe) and one for the lift  
- DRV8833 dual H-bridge drivers for independent motor channels  
- ESP32-S3 DevKit-C Wi-Fi server with built-in web interface (no BLE required)  
- REST-style API: `/api/drive?x=&y=&rot=&lift=` for remote commands  
- Auto-stop timeout for safety if no commands are received  
- Fully modular, split-file Arduino architecture  

---

## 🚀 Getting Started

### 1️⃣ Hardware Assembly
- Mount N20 motors and wheels to the base chassis.  
- Assemble scissor lift mechanism and attach the lead-screw motor.  
- Wire motors to DRV8833 boards (1 board for drive, 1 for lift).  
- Connect drivers to the ESP32-S3 DevKit-C pins (as set in `config.h`).  
- Connect status LED to GPIO 48 (if using).  

### 2️⃣ Software Setup
1. Install [Arduino IDE](https://www.arduino.cc/en/software).  
2. Install the ESP32 Board Manager URL: https://dl.espressif.com/dl/package_esp32_index.json

3. Select **ESP32S3 Dev Module** and correct COM port.  
4. Open `Lil_h_Drive.ino` and update `config.h` with your Wi-Fi SSID and password.  
5. Upload the sketch and monitor serial output (115200 baud) for the IP address.  
6. Open the IP in a browser — you’ll see the Lil H Drive web UI (sliders + D-pad).  

---

## 🌐 Web Interface

Served directly from flash (PROGMEM), no SPIFFS/LittleFS required.  
Endpoints:
| Route | Description |
|-------|--------------|
| `/` | HTML UI page |
| `/api/drive?x=&y=&rot=&lift=` | Motor control endpoint |
| `/api/ping` | Connection check |

Example request:
GET /api/drive?x=0&y=80&rot=0&lift=20
→ {"ok":true,"x":0,"y":80,"rot":0,"lift":20}

---

## 🛠️ Future Improvements
- Encoder feedback for closed-loop motor control  
- ToF/Ultrasonic sensors for obstacle avoidance  
- Battery voltage telemetry in web UI  
- ROS 2 bridge integration  
- Optional BLE remote control mode  

---

## 📁 Repository Structure
Lil_h_Drive/
├─ Lil_h_Drive.ino
├─ config.h
├─ motor_control.cpp/.h
├─ web_server.cpp/.h
├─ ui_html.cpp/.h
├─ models/ # (future) STL & Fusion 360 files
├─ docs/ # Schematics, images, wiring PDFs
├─ LICENSE
└─ README.md

---

## ⚖️ License
**Lil H Drive — Personal Use License (No Resale)**  
Free for personal projects and educational use.  
Commercial use requires written permission from the author.  
See [LICENSE](./LICENSE) for full terms.

---

### 🧑‍🔧 Author
**Matthew Winter**  
Automation Engineer | Robotics & Embedded Systems  

---
