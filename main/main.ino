#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>
#include "faceDisplay.hpp"
#include "motionSensor.hpp"
#include "powerManager.hpp"

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
#define SCREEN_ADDRESS 0x3C

// Global display object (used in emotions.cpp)
Adafruit_SH1106G display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void setup() {
  Serial.begin(115200);
  Wire.begin(21, 22); // SDA = 21, SCL = 22 for ESP32

  // Initialize display
  if (!display.begin(SCREEN_ADDRESS, true))
  {
    Serial.println(F("Display allocation failed"));
    for (;;);
  }

  display.clearDisplay();
  display.display();
  delay(500);

  // Detect wakeup reason
  esp_sleep_wakeup_cause_t wakeup_reason = esp_sleep_get_wakeup_cause();
  if (wakeup_reason == ESP_SLEEP_WAKEUP_EXT1)
  {
    Serial.println("Woke up from motion!");
    // Reset idle timer after waking up
    resetIdleTimer();
    // Wake up animation
    enterWakeUpState();
    
  }
  else
  {
    Serial.println("Normal power-on boot");
    // Wake up animation
  }

  // Initialize motion sensors
  initMotionRightSensor(MOTION_PIN_RIGHT);
  initMotionLeftSensor(MOTION_PIN_LEFT);
  resetIdleTimer();
}

void loop() {
  lookCenterSequence();

  if (isMotionBothDirDetected())
  {
    lookBothDirSequence();
    resetIdleTimer();
  }
  else if (isMotionRightDetected())
  {
    lookRightSequence();
    resetIdleTimer();
  }
  else if (isMotionLeftDetected())
  {
    lookLeftSequence();
    resetIdleTimer();
  }
  else
  {
    Serial.println("No motion.");
    displayHappyEmo();
    checkIdleAndSleep();
  }

  delay(50);
}
