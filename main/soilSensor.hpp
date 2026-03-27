#ifndef SOIL_SENSOR_HPP
#define SOIL_SENSOR_HPP

#include <Arduino.h>

#define SOIL_PIN 34  // Analog pin for soil moisture sensor (can be changed)
#define DRY_VALUE 4095  // Analog value when soil is dry
#define WET_VALUE 1000  // Analog value when soil is wet (adjust after testing)

/**
 * @brief Initialize the soil moisture sensor
 */
void initSoilSensor();

/**
 * @brief Read the raw analog value from the soil sensor
 * @return Raw analog reading (0–4095)
 */
int readSoilRaw();

/**
 * @brief Get soil moisture as a percentage (0–100%)
 * @return Moisture percentage
 */
int getSoilMoisturePercent();

/**
 * @brief Print the soil moisture value to Serial monitor
 */
void printSoilStatus();

#endif
