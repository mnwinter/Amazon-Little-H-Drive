#pragma once
#include <Arduino.h>

// Initialize pins and any timers
void motor_init();

// Drive command in percentage -100..100 for each axis
// x = strafe (center wheel), y = forward/back, rot = rotation (left/right differential)
// lift = -100..100 for lift down/up
void motor_drive(int x, int y, int rot, int lift);

// Immediately stop all motion
void motor_stop();
