#ifndef SOIL_SENSOR_HPP
#define SOIL_SENSOR_HPP

#include <Arduino.h>

#define SOIL_PIN 34  // Analog pin for soil moisture sensor (can be changed)
#define DRY_VALUE 4095  // Analog value when soil is dry
#define WET_VALUE 1000  // Analog value when soil is wet (adjust after testing)

void initSoilSensor();
int readSoilRaw();
int getSoilMoisturePercent();
void printSoilStatus();
bool getWateringStatusFlg(int oldPercent, int newPercent);

#endif
