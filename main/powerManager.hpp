#ifndef POWERMANAGER_HPP
#define POWERMANAGER_HPP

#include <Arduino.h>

// Duration (in milliseconds) of no activity before sleep
#define IDLE_TIMEOUT 30000  // 30 seconds

void checkIdleAndSleep();
void resetIdleTimer();
void enterDeepSleep();
void enterWakeUpState();

#endif
