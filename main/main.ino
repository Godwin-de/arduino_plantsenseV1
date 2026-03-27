#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>
// #include <RTClib.h>
#include "faceDisplay.hpp"
#include "motionSensor.hpp"
#include "powerManager.hpp"
#include "soilSensor.hpp"
// #include "timelyReminders.hpp"


#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
#define SCREEN_ADDRESS 0x3C

// Global display object (used in emotions.cpp)
Adafruit_SH1106G display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// RTC_DS3231 rtc;

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
  initSoilSensor();
  initMotionRightSensor(MOTION_PIN_RIGHT);
  initMotionLeftSensor(MOTION_PIN_LEFT);
  resetIdleTimer();

  // Initialize RTC for time-based features
  // if (!rtc.begin())
  // {
  //   Serial.println("Couldn't find RTC");
  //   while (1);
  // }

  // if (rtc.lostPower())
  // {
  //   Serial.println("RTC lost power, setting time!");
  //   // Set RTC to the date & time this sketch was compiled
  //   rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  // }
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
    displayHappyEmo(); //TEMP
    checkIdleAndSleep(); //TEMP
  }

  // CHECK TIMELY REMINDER
  // for (int i = 0; i < numAffirmations; i++)
  // {
  //   DateTime now = rtc.now();

  //   if ( (now.hour() == timelyReminders[i].hour)
  //   && (now.minute() == timelyReminders[i].minute)
  //   && (now.second() == timelyReminders[i].second)
  //   )
  //   {
  //     Serial.println(timelyReminders[i].message);
  //     // displayMotivationEmo(); // your custom function
  //     delay(1000); // prevent multiple triggers
  //   }
  // }

  // CONTINUOUS MONITORING OF SOIL MOISTURE LEVELS (dito magbabase ng emotion displays)
  // kada magdidilig, kailangan natin isave yung cuurrent state/emotion to analyze streak
  printSoilStatus();
  Serial.println("TEST: " + String(readSoilRaw()));

  delay(50);
}
