#pragma once

// -----------------------------
// Lil H Drive - configuration
// Board: ESP32-S3 DevKit-C
// -----------------------------

// ---- Wi-Fi (Access existing network) ----
#define WIFI_SSID      "CHANGE_ME"
#define WIFI_PASSWORD  "CHANGE_ME"

// ---- Web server ----
#define WEB_SERVER_PORT   80

// ---- Status RGB / LED ----
// You mentioned RGB on GPIO 48. If using a single LED (not WS2812), treat as status pin.
// If using a WS2812/Neopixel, integrate your preferred library in motor_control.cpp.
// For now we use it as a basic status output.
#define STATUS_RGB_PIN  48

// ---- DRV8833 pin assignments ----
// Set these to your wiring. All pins are placeholders; adjust for your build.
// Left drive motor
#ifndef LEFT_IN1
  #define LEFT_IN1   5
#endif
#ifndef LEFT_IN2
  #define LEFT_IN2   6
#endif

// Right drive motor
#ifndef RIGHT_IN1
  #define RIGHT_IN1  7
#endif
#ifndef RIGHT_IN2
  #define RIGHT_IN2  8
#endif

// Center "H" motor (strafe)
#ifndef STRAFE_IN1
  #define STRAFE_IN1 9
#endif
#ifndef STRAFE_IN2
  #define STRAFE_IN2 10
#endif

// Lift motor
#ifndef LIFT_IN1
  #define LIFT_IN1   11
#endif
#ifndef LIFT_IN2
  #define LIFT_IN2   12
#endif

// ---- Optional PWM speed control (enable pins) ----
// If your DRV8833 boards expose PWM enable pins, set them here; otherwise leave as -1.
#ifndef LEFT_PWM
  #define LEFT_PWM   -1
#endif
#ifndef RIGHT_PWM
  #define RIGHT_PWM  -1
#endif
#ifndef STRAFE_PWM
  #define STRAFE_PWM -1
#endif
#ifndef LIFT_PWM
  #define LIFT_PWM   -1
#endif

// ---- Motor inversion flags ----
#define MOTOR_INVERT_LEFT    false
#define MOTOR_INVERT_RIGHT   true
#define MOTOR_INVERT_STRAFE  false
#define MOTOR_INVERT_LIFT    false

// ---- Defaults / safety ----
#define CMD_DEADBAND       3        // ignore tiny joystick noise (%)
#define CMD_SCALE_MAX      100      // expected range -100..100
#define COMMAND_TIMEOUT_MS 500      // stop if no command within this time
