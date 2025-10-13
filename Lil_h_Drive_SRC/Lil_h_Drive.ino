/*
  Lil H Drive — ESP32‑S3 DevKit‑C
  Split-file Arduino project.

  Files:
    - config.h            pins, wifi settings
    - motor_control.*     motor init + drive mixing
    - web_server.*        wifi + http server + routes
    - ui_html.*           index_html page in PROGMEM

  Notes:
    - Uses built-in WebServer (no AsyncWebServer dependency)
    - Open Serial Monitor @115200 to see IP after boot.
*/

#include <Arduino.h>
#include "config.h"
#include "motor_control.h"
#include "web_server.h"

void setup() {
  Serial.begin(115200);
  delay(100);
  Serial.println();
  Serial.println("Lil H Drive booting...");

  motor_init();
  webserver_begin();
}

void loop() {
  webserver_handle();
  // Add any periodic tasks here
}
