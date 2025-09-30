/*
 * XIAO ESP32S3 — BLE UART (Nordic UART Service) — ESP32 core 3.x compatible
 * - Service UUID: 6E400001-B5A3-F393-E0A9-E50E24DCCA9E
 * - RX (Write):   6E400002-B5A3-F393-E0A9-E50E24DCCA9E
 * - TX (Notify):  6E400003-B5A3-F393-E0A9-E50E24DCCA9E
 * Onboard LED: GPIO 21 (active-low)
 */

#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>
// NOTE: Do NOT include BLE2902 or add it manually on ESP32 core 3.x (NimBLE)

#ifndef LED_BUILTIN
  #define LED_BUILTIN 21  // XIAO ESP32S3 amber LED (active-low)
#endif

static BLEUUID SERVICE_UUID   ("6E400001-B5A3-F393-E0A9-E50E24DCCA9E");
static BLEUUID CHAR_UUID_RX   ("6E400002-B5A3-F393-E0A9-E50E24DCCA9E"); // phone -> ESP (Write)
static BLEUUID CHAR_UUID_TX   ("6E400003-B5A3-F393-E0A9-E50E24DCCA9E"); // ESP -> phone (Notify)

BLEServer*         pServer   = nullptr;
BLECharacteristic* pTxChar   = nullptr;
BLECharacteristic* pRxChar   = nullptr;
bool deviceConnected         = false;
unsigned long lastBeatMs     = 0;

class ServerCallbacks : public BLEServerCallbacks {
  void onConnect(BLEServer* s) override {
    deviceConnected = true;
    Serial.println("BLE: Phone connected");
  }
  void onDisconnect(BLEServer* s) override {
    deviceConnected = false;
    Serial.println("BLE: Phone disconnected");
    s->getAdvertising()->start();
  }
};

class RxCallbacks : public BLECharacteristicCallbacks {
  void onWrite(BLECharacteristic* c) override {
    // On ESP32 core 3.x this is an Arduino String
    String s = c->getValue();
    if (s.length() == 0) return;

    // Print exactly what came in
    Serial.print("RX: ");
    Serial.print(s);
    Serial.println();

    // Blink LED (active-low)
    digitalWrite(LED_BUILTIN, LOW);
    delay(30);
    digitalWrite(LED_BUILTIN, HIGH);

    // Echo back via notify (works once the phone enables notifications)
    if (deviceConnected && pTxChar) {
      pTxChar->setValue((uint8_t*)s.c_str(), s.length());
      pTxChar->notify();
    }
  }
};

void setup() {
  Serial.begin(115200);
  delay(500);
  Serial.println("\nXIAO ESP32S3 BLE UART (ESP32 core 3.x)");

  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH); // OFF (active-low)

  BLEDevice::init("XIAO-ESP32S3-UART");
  // Optional (safe on 3.x): boost TX power & request larger MTU
  // BLEDevice::setPower(ESP_PWR_LVL_P7);
  // BLEDevice::setMTU(185);

  pServer = BLEDevice::createServer();
  pServer->setCallbacks(new ServerCallbacks());

  BLEService* pService = pServer->createService(SERVICE_UUID);

  // TX: Notify
  pTxChar = pService->createCharacteristic(
    CHAR_UUID_TX,
    BLECharacteristic::PROPERTY_NOTIFY
  );
  // No BLE2902 added manually on NimBLE/3.x

  // RX: Write / Write No Resp
  pRxChar = pService->createCharacteristic(
    CHAR_UUID_RX,
    BLECharacteristic::PROPERTY_WRITE | BLECharacteristic::PROPERTY_WRITE_NR
  );
  pRxChar->setCallbacks(new RxCallbacks());

  pService->start();

  BLEAdvertising* adv = BLEDevice::getAdvertising();
  adv->addServiceUUID(SERVICE_UUID);
  adv->setScanResponse(true);
  adv->setMinPreferred(0x06); // helps iOS
  adv->setMinPreferred(0x12);
  BLEDevice::startAdvertising();

  Serial.println("Advertising as XIAO-ESP32S3-UART. Use nRF Connect to connect & enable TX notifications.");
}

void loop() {
  if (deviceConnected && millis() - lastBeatMs > 5000) {
    lastBeatMs = millis();
    const char* msg = "Hello from XIAO S3\n";
    pTxChar->setValue((uint8_t*)msg, strlen(msg));
    pTxChar->notify();
    Serial.println("TX: heartbeat sent");
  }
}
