# Mini H Drive Robot

A compact RC robot inspired by Amazon Drive Units, featuring a scissor-lift mechanism, N20 motors, and an ESP32-S3 microcontroller for wireless control and expansion.  

This repository documents the hardware, electronics, and firmware used to design and build the robot.  

---

## 📦 Bill of Materials (BOM)

### 🔹 Motors & Wheels
- [MECCANIXITY 2pcs 200RPM Micro Gear Motor with Encoder, N20 DC12V Gearbox](https://www.amazon.com/dp/B0BHRY9L6Q) – Amazon  
- [N20 DC Motor with Magnetic Encoder – 6V, 1:100 Gear Ratio (ID 4639)](https://www.adafruit.com/product/4639) – Adafruit  
- [RecDec 4 Pack Mini Micro N20 Gear Motor Wheels, 3mm Shaft D-Hole Rubber Tire](https://www.amazon.com/dp/B09H1NVQH5) – Amazon  
- [DC 6V/12V Speed Reduction Gear Motor with T5 160mm Screw Thread Shaft + Brass Nut](https://www.amazon.com/dp/B09K3STYVQ) – Amazon  

### 🔹 Motor Drivers
- [WWZMDiB 6pcs DRV8833 DC Motor Driver Controller Board, 1.5A Dual H-Bridge](https://www.amazon.com/dp/B0C5W3XYMC) – Amazon  

### 🔹 Microcontroller & Expansion
- [XIAO ESP32S3 (3PCS Pack – WiFi + BLE, 8MB PSRAM, 8MB Flash)](https://www.amazon.com/dp/B0C3ZRVFHK) – Amazon  
- [Seeeduino XIAO Expansion Board – Quick Prototyping, CircuitPython Supported](https://www.amazon.com/dp/B09WZTXS2P) – Amazon  
- [Seeed Studio XIAO Expansion Board (Grove OLED, UART, Analog/Digital)](https://www.seeedstudio.com/Expansion-board-for-XIAO-Series-p-4869.html) – Seeed Studio  
- [Seeed Studio XIAO ESP32-S3 (3PCS)](https://www.seeedstudio.com/XIAO-ESP32S3-p-5627.html) – Seeed Studio  

---

## 📚 Documentation & References
- [High-Performance Dev Board with Wi-Fi and BLE – XIAO ESP32S3](https://www.seeedstudio.com/XIAO-ESP32S3-p-5627.html)  
- [ESP32-S3 Datasheet (PDF)](https://www.espressif.com/sites/default/files/documentation/esp32-s3_datasheet_en.pdf)  
- [Getting Started with Seeed Studio XIAO ESP32S3 Series](https://wiki.seeedstudio.com/xiao_esp32s3_getting_started/)  
- [Bluetooth for both versions – Seeed Studio Wiki](https://wiki.seeedstudio.com/xiao_esp32s3_ble/)  
- [Expansion Board Base for XIAO – Seeed Studio Wiki](https://wiki.seeedstudio.com/xiao_expansion_board/)  
- [Global Robotics University](https://globalroboticsuniversity.com)  

---

## ⚙️ Features
- Dual N20 gear motors for drive, controlled via DRV8833 H-bridge modules.  
- Dedicated N20 screw-drive motor for scissor-lift actuation.  
- XIAO ESP32-S3 microcontroller for wireless RC control (Bluetooth/Wi-Fi).  
- Encoder support for precise drive tracking (future feature).  
- Compact expansion board for prototyping and Grove connectivity.  

---

## 🚀 Getting Started

1. **Hardware Assembly**
   - Mount N20 motors with wheels for the drive base.  
   - Install lift mechanism with screw-drive N20 motor and brass nut.  
   - Connect motors to DRV8833 drivers (1 driver for base, 1 driver for lift).  
   - Wire drivers to XIAO ESP32-S3 through expansion board headers.  

2. **Software Setup**
   - Install [Arduino IDE](https://www.arduino.cc/en/software) or [PlatformIO](https://platformio.org/).  
   - Add Seeed Studio XIAO ESP32-S3 board package.  
   - Upload firmware from `src/` folder in this repo.  

3. **Control**
   - Default firmware uses Bluetooth (BLE) for RC control.  
   - Wi-Fi/WebSocket control option is also available (see `/examples`).  

---

## 🛠️ Future Improvements
- Integrate ToF/Ultrasonic sensors for obstacle avoidance.  
- Encoder feedback for closed-loop drive control.  
- ROS2 integration for advanced autonomy.  
- Battery monitoring & charging circuit design.  

---

## 📜 License
This project is licensed under the MIT License. See [LICENSE](LICENSE) for details.  

---
