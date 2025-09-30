/*
  XIAO ESP32S3 — Minimal Self-Test (LED + Serial)
  - Blinks the onboard USER LED on GPIO 21 (active-low)
  - Prints status to Serial at 115200 baud
*/

#ifndef LED_BUILTIN
  #define LED_BUILTIN 21   // XIAO ESP32S3 user LED (active-low)
#endif

void setup() {
  Serial.begin(115200);
  delay(500);
  Serial.println("XIAO ESP32S3 self-test starting...");

  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH); // HIGH = LED OFF (active-low)
}

void loop() {
  // ON
  digitalWrite(LED_BUILTIN, LOW);  // LOW = LED ON
  Serial.println("LED ON");
  delay(500);

  // OFF
  digitalWrite(LED_BUILTIN, HIGH); // HIGH = LED OFF
  Serial.println("LED OFF");
  delay(500);
}
