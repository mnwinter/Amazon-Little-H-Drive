#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>

void setup() {
  Serial.begin(115200);
  Serial.println("Starting BLE test...");

  // Create BLE device
  BLEDevice::init("XIAO-ESP32S3-BLE");

  // Create BLE server
  BLEServer *pServer = BLEDevice::createServer();

  // Start advertising
  BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
  pAdvertising->start();

  Serial.println("BLE advertising started. Open a BLE scanner app on your phone!");
}

void loop() {
  delay(2000);
  Serial.println("Still advertising...");
}
