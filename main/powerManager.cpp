#include "powerManager.hpp"
#include "motionSensor.hpp"
#include "faceDisplay.hpp"
#include <Adafruit_SH110X.h>
#include <Wire.h>
#include <esp_sleep.h>

// Track the last activity time
static unsigned long lastActivityTime = 0;

// Track if we already started sleep
static bool isSleeping = false;

// External display object from main
extern Adafruit_SH1106G display;

/*/////////////////////////////////////////////////////////////////////////////////////////////////////////
// --- Reset idle timer when motion is detected ---
/////////////////////////////////////////////////////////////////////////////////////////////////////////*/
void resetIdleTimer()
{
    lastActivityTime = millis();
    isSleeping = false; // wake up from sleep, reset flag
}

/*/////////////////////////////////////////////////////////////////////////////////////////////////////////
// --- Check for idle timeout and enter sleep if needed ---
/////////////////////////////////////////////////////////////////////////////////////////////////////////*/
void checkIdleAndSleep()
{
    if (!isSleeping && (millis() - lastActivityTime > IDLE_TIMEOUT))
    {
        Serial.println("⚡ System idle — entering sleep mode...");
        enterDeepSleep();
        isSleeping = true; // mark that sleep sequence started
    }
}

/*/////////////////////////////////////////////////////////////////////////////////////////////////////////
// --- Enter deep sleep with eye-closing animation ---
/////////////////////////////////////////////////////////////////////////////////////////////////////////*/
void enterDeepSleep()
{
    Serial.println("Starting sleep animation...");

    // --- Eye-closing animation ---
    for (int h = 20; h >= 2; h -= 3) {
        lookCenter(h, 4);  // gradually close eyes
        delay(100);
    }

    for (int h = 2; h <= 20; h += 2) {
        lookCenter(h, 2);  // small blink before full sleep
        delay(60);
    }

    for (int h = 20; h >= 0; h -= 4) {
        lookCenter(h, 1);  // fully closed
        delay(80);
    }

    // Final sleeping face text
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(SH110X_WHITE);
    display.setCursor(45, 25);
    display.print("Z z z...");
    display.display();
    delay(500);

    Serial.println("Display off. Going to deep sleep...");

    // Configure wake-up source (any motion sensor HIGH wakes up)
    esp_sleep_enable_ext1_wakeup(
        (1ULL << MOTION_PIN_RIGHT) | (1ULL << MOTION_PIN_LEFT),
        ESP_EXT1_WAKEUP_ANY_HIGH
    );

    // Enter deep sleep
    esp_deep_sleep_start();
}
