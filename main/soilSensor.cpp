#include "soilSensor.hpp"

/**
 * @brief Initialize the soil sensor pin
 */
void initSoilSensor() {
    pinMode(SOIL_PIN, INPUT);
    Serial.println("🌱 Soil sensor initialized");
}

/**
 * @brief Read the raw analog signal from the sensor
 */
int readSoilRaw() {
    return analogRead(SOIL_PIN);
}

/**
 * @brief Convert raw analog signal to percentage
 *        (0% = dry, 100% = wet)
 */
int getSoilMoisturePercent() {
    int rawValue = readSoilRaw();
    // Map reading to percentage (adjust DRY_VALUE/WET_VALUE for calibration)
    int percent = map(rawValue, DRY_VALUE, WET_VALUE, 0, 100);
    percent = constrain(percent, 0, 100);
    // return percent;

    return 50; //temp for testing purposes
}

/**
 * @brief Print soil moisture status
 */
void printSoilStatus() {
    int rawValue = readSoilRaw();
    int percent = getSoilMoisturePercent();

    Serial.print("Soil Moisture Raw: ");
    Serial.print(rawValue);
    Serial.print(" | Moisture: ");
    Serial.print(percent);
    Serial.println("%");
}

/**
 * @brief check if system receives water
 */
bool getWateringStatusFlg(int oldPercent, int newPercent) {
    // if the new soil moisture percentage is higher than the old one, it means the plant is being watered
    return (newPercent > oldPercent);
}
