#include "motor_control.h"
#include "config.h"

// Helper to apply inversion
static inline int applyInvert(int val, bool invert) {
  return invert ? -val : val;
}

// Map -100..100 to a simple HIGH/LOW for direction, optional PWM for speed
// For DRV8833: IN1/IN2 control direction; optional PWM on one/both pins if wired.
static void driveHBridge(int in1, int in2, int pwmPin, int percent) {
  percent = constrain(percent, -100, 100);
  if (percent == 0) {
    // Brake low
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
    if (pwmPin >= 0) analogWrite(pwmPin, 0);
    return;
  }
  bool forward = percent > 0;
  int duty = map(abs(percent), 0, 100, 0, 255);

  if (pwmPin >= 0) {
    // Direction via IN pins, speed via PWM
    digitalWrite(in1, forward ? HIGH : LOW);
    digitalWrite(in2, forward ? LOW  : HIGH);
    analogWrite(pwmPin, duty);
  } else {
    // No PWM pin: simple on/off at full power proportional logic
    // (We still set direction; "speed" cannot be modulated without PWM.)
    digitalWrite(in1, forward ? HIGH : LOW);
    digitalWrite(in2, forward ? LOW  : HIGH);
  }
}

void motor_init() {
  // Status pin
  pinMode(STATUS_RGB_PIN, OUTPUT);
  digitalWrite(STATUS_RGB_PIN, LOW);

  // Drive pins
  pinMode(LEFT_IN1, OUTPUT);
  pinMode(LEFT_IN2, OUTPUT);
  pinMode(RIGHT_IN1, OUTPUT);
  pinMode(RIGHT_IN2, OUTPUT);
  pinMode(STRAFE_IN1, OUTPUT);
  pinMode(STRAFE_IN2, OUTPUT);
  pinMode(LIFT_IN1, OUTPUT);
  pinMode(LIFT_IN2, OUTPUT);

  if (LEFT_PWM >= 0)  pinMode(LEFT_PWM, OUTPUT);
  if (RIGHT_PWM >= 0) pinMode(RIGHT_PWM, OUTPUT);
  if (STRAFE_PWM >= 0)pinMode(STRAFE_PWM, OUTPUT);
  if (LIFT_PWM >= 0)  pinMode(LIFT_PWM, OUTPUT);

  motor_stop();

  // Blink status to show motor init
  digitalWrite(STATUS_RGB_PIN, HIGH);
  delay(100);
  digitalWrite(STATUS_RGB_PIN, LOW);
}

void motor_drive(int x, int y, int rot, int lift) {
  // Apply deadband
  auto filter = [](int v)->int { return (abs(v) < CMD_DEADBAND) ? 0 : v; };
  x = filter(x); y = filter(y); rot = filter(rot); lift = filter(lift);

  // Constrain inputs
  x   = constrain(x,  -CMD_SCALE_MAX, CMD_SCALE_MAX);
  y   = constrain(y,  -CMD_SCALE_MAX, CMD_SCALE_MAX);
  rot = constrain(rot,-CMD_SCALE_MAX, CMD_SCALE_MAX);
  lift= constrain(lift,-CMD_SCALE_MAX, CMD_SCALE_MAX);

  // H-drive mixing:
  // Left  = y + rot
  // Right = y - rot
  // Strafe (center) = x
  int leftPct  = applyInvert(y + rot, MOTOR_INVERT_LEFT);
  int rightPct = applyInvert(y - rot, MOTOR_INVERT_RIGHT);
  int strafePct= applyInvert(x,       MOTOR_INVERT_STRAFE);
  int liftPct  = applyInvert(lift,    MOTOR_INVERT_LIFT);

  // Saturate to -100..100
  leftPct   = constrain(leftPct,   -100, 100);
  rightPct  = constrain(rightPct,  -100, 100);
  strafePct = constrain(strafePct, -100, 100);
  liftPct   = constrain(liftPct,   -100, 100);

  driveHBridge(LEFT_IN1,  LEFT_IN2,  LEFT_PWM,   leftPct);
  driveHBridge(RIGHT_IN1, RIGHT_IN2, RIGHT_PWM,  rightPct);
  driveHBridge(STRAFE_IN1,STRAFE_IN2,STRAFE_PWM, strafePct);
  driveHBridge(LIFT_IN1,  LIFT_IN2,  LIFT_PWM,   liftPct);
}

void motor_stop() {
  digitalWrite(LEFT_IN1, LOW);   digitalWrite(LEFT_IN2, LOW);
  digitalWrite(RIGHT_IN1, LOW);  digitalWrite(RIGHT_IN2, LOW);
  digitalWrite(STRAFE_IN1, LOW); digitalWrite(STRAFE_IN2, LOW);
  digitalWrite(LIFT_IN1, LOW);   digitalWrite(LIFT_IN2, LOW);

  if (LEFT_PWM >= 0)  analogWrite(LEFT_PWM, 0);
  if (RIGHT_PWM >= 0) analogWrite(RIGHT_PWM, 0);
  if (STRAFE_PWM >= 0)analogWrite(STRAFE_PWM, 0);
  if (LIFT_PWM >= 0)  analogWrite(LIFT_PWM, 0);
}
