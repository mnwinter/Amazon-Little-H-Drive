#include "web_server.h"
#include "config.h"
#include "motor_control.h"
#include "ui_html.h"

#include <WiFi.h>
#include <WebServer.h>

static WebServer server(WEB_SERVER_PORT);

static unsigned long lastCmdMs = 0;

// Parse int with default
static int qint(const String& name, int def=0) {
  if (!server.hasArg(name)) return def;
  return server.arg(name).toInt();
}

static void handle_root() {
  server.setContentLength(CONTENT_LENGTH_UNKNOWN);
  server.send(200, "text/html");
  // Stream from PROGMEM
  WiFiClient client = server.client();
  const char* p = index_html;
  // simple streamer (index_html is small)
  server.sendContent_P(index_html);
}

static void handle_drive() {
  int x   = qint("x", 0);
  int y   = qint("y", 0);
  int rot = qint("rot", 0);
  int lift= qint("lift", 0);

  motor_drive(x, y, rot, lift);
  lastCmdMs = millis();

  String json = "{\"ok\":true,\"x\":" + String(x) +
                ",\"y\":" + String(y) +
                ",\"rot\":" + String(rot) +
                ",\"lift\":" + String(lift) + "}";
  server.send(200, "application/json", json);
}

static void handle_ping() {
  server.send(200, "application/json", "{\"ok\":true}");
}

void webserver_begin() {
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  Serial.print("Connecting to WiFi ");
  Serial.print(WIFI_SSID);
  Serial.print(" ...");

  unsigned long t0 = millis();
  while (WiFi.status() != WL_CONNECTED && (millis() - t0) < 15000) {
    delay(250);
    Serial.print(".");
  }
  Serial.println();

  if (WiFi.status() == WL_CONNECTED) {
    Serial.print("WiFi connected. IP: ");
    Serial.println(WiFi.localIP());
    digitalWrite(STATUS_RGB_PIN, HIGH);
  } else {
    Serial.println("WiFi failed to connect. Starting AP fallback...");
    WiFi.mode(WIFI_AP);
    WiFi.softAP("Lil_H_Drive", "lilhdrive");
    Serial.print("AP IP: ");
    Serial.println(WiFi.softAPIP());
    digitalWrite(STATUS_RGB_PIN, LOW);
  }

  server.on("/", HTTP_GET, handle_root);
  server.on("/api/drive", HTTP_GET, handle_drive);
  server.on("/api/ping", HTTP_GET, handle_ping);
  server.onNotFound([](){
    server.send(404, "text/plain", "Not found");
  });

  server.begin();
  Serial.println("HTTP server started.");
}

void webserver_handle() {
  server.handleClient();

  // Safety stop if stale
  if ((millis() - lastCmdMs) > COMMAND_TIMEOUT_MS) {
    motor_stop();
  }
}
