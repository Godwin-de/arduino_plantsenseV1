#include <WiFi.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>
// #include <RTClib.h>

#include "faceDisplay.hpp"
#include "motionSensor.hpp"
#include "powerManager.hpp"
#include "soilSensor.hpp"
#include "affirmationMessages.hpp"
#include "engagementIndicator.hpp"
#include "backupSystemAccess.hpp"
#include "quotes.hpp"


#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
#define SCREEN_ADDRESS 0x3C
#define API_RETRY_LIMIT 10

// Global display object
Adafruit_SH1106G display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Global datetime object
// RTC_DS3231 rtc;

// Global variables for soil moisture tracking
int oldSoilMoisturePercent = 0;
int newSoilMoisturePercent = 0;

// For API usage
int apiRetryCount = 0;


void setup() {
  Serial.begin(115200);
  Wire.begin(21, 22); // SDA = 21, SCL = 22 for ESP32

  ///////////////////////////////////////
  // Initialize display
  if (!display.begin(SCREEN_ADDRESS, true))
  {
    Serial.println(F("Display allocation failed"));
    for (;;);
  }

  display.clearDisplay();
  display.display();
  delay(500);

  ///////////////////////////////////////
  // Preparing to connect on live API for affirmation messages  
  WiFi.begin(ssid, password);
  while ((WiFi.status() != WL_CONNECTED) && (apiRetryCount <= API_RETRY_LIMIT)) {
    // Connecting attempt
    displayWifiLoadingAnimation(3, 150);  
    apiRetryCount++;
  }
 
  bool isConnected = (WiFi.status() == WL_CONNECTED);
  displayWifiConnectionStatus(isConnected); // connection result display

  ///////////////////////////////////////
  // Detect wakeup reason
  esp_sleep_wakeup_cause_t wakeup_reason = esp_sleep_get_wakeup_cause();
  if (wakeup_reason == ESP_SLEEP_WAKEUP_EXT1)
  {
    Serial.println("Woke up from motion!");
    // Wake up animation
    enterWakeUpState();
    resetIdleTimer();
    
  }
  else
  {
    Serial.println("Normal power-on boot");
    // Wake up animation
    enterWakeUpState();
    resetIdleTimer();
  }

  ///////////////////////////////////////
  // Read moisture sensor once at startup
  initSoilSensor();
  newSoilMoisturePercent = getSoilMoisturePercent();
  oldSoilMoisturePercent = newSoilMoisturePercent;

  ///////////////////////////////////////
  // Initialize motion sensors
  initMotionRightSensor(MOTION_PIN_RIGHT);
  initMotionLeftSensor(MOTION_PIN_LEFT);

  ///////////////////////////////////////
  // Initialize persistent backup data
  loadStreakData();

  ///////////////////////////////////////
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
  // CHECK TIMELY REMINDER
  // for (int i = 0; i < numTimelyReminders; i++)
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

  /////////////////////////////////////////////////////// TODO - randomizer of actions to prevent habituation (e.g. different face displays, different wake up animations, etc.)
  oldSoilMoisturePercent = newSoilMoisturePercent;
  newSoilMoisturePercent = getSoilMoisturePercent();

  bool isWatered = getWateringStatusFlg(oldSoilMoisturePercent, newSoilMoisturePercent);

  lookCenterSequence();

  // Check if plant is being watered based on soil moisture changes
  if ( isWatered )
  {
    Serial.println("Plant is being watered! 💧");

    // Update engagement streak system
    int currentEmotion = getCurrentEmotion();
    updateEngagementStreak(currentEmotion);

    int currentStreakPoints = getCurrentStreakValues();
    updateUnlockTierLevelStreak(currentStreakPoints);

    Serial.println("Current Streak Indicator: " + String(currentStreakPoints));

    // Display affirmation message
    String affirmationMsg = "";
    bool isConnected = (WiFi.status() == WL_CONNECTED); 

    if( isConnected ) {
      // Try fetching quote from API
      affirmationMsg = fetchAndDisplayQuote(true);

      if (affirmationMsg == notConnectedMsg) {
        // If API call failed, fallback to local messages
        affirmationMsg = getAffirmationMessage();
      }
    }
    else {
      affirmationMsg = getAffirmationMessage();
    }
  
    // Display the affirmation message (from API or local)
    displayAffirmationMessage(affirmationMsg.c_str());
    
    // reset idle timer on watering activity
    resetIdleTimer();
  }

  if (isMotionBothDirDetected())
  {
    // If motion detected in both directions, look center with a blink
    lookBothDirSequence();

    // Reset idle timer after motion activity
    resetIdleTimer();
  }
  else if (isMotionRightDetected())
  {
    // If motion detected on the right, look right
    lookRightSequence();
    
    // Reset idle timer after motion activity
    resetIdleTimer();
  }
  else if (isMotionLeftDetected())
  {
    // If motion detected on the left, look left
    lookLeftSequence();

    // Reset idle timer after motion activity
    resetIdleTimer();
  }
  else
  {
    // Determine emotion based on soil moisture percentage and display appropriate emotion
    showEmotion(newSoilMoisturePercent);

    // Check if idle time has exceeded threshold and enter sleep mode if needed
    checkIdleAndSleep();
  }

  newSoilMoisturePercent = 49; //temp for testing purposes





  ////////////////////////////////////////////////////////

  delay(50);
}
