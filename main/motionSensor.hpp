#ifndef MOTIONSENSOR_HPP
#define MOTIONSENSOR_HPP

#include <Arduino.h>

#define MOTION_PIN_RIGHT 4
#define MOTION_PIN_LEFT 2

void initMotionRightSensor(int pin);
void initMotionLeftSensor(int pin);
bool isMotionRightDetected();
bool isMotionLeftDetected();
bool isMotionBothDirDetected();

#endif
