#include <Arduino.h>

#include "affirmationMessages.hpp"



TimeStamp timelyReminders[] = {
  {11, 48, 0, "🌞 Good morning! Stay positive today."},
  {11, 50, 0, "🍴 Lunchtime reminder: nourish yourself well."},
  {12, 0, 0, "🌇 Evening check-in: you did great today."},
  {12, 10, 0, "🌙 Wind down, tomorrow is another chance."}
};

const int numTimelyReminders = sizeof(timelyReminders) / sizeof(timelyReminders[0]);

const char* affirmations[] = {
  "Thanks for watering! Stay strong.",
  "Thanks for watering! Keep growing.",
  "Thanks for watering! Choose joy.",
  "Thanks for watering! Shine bright.",
  "Thanks for watering! Believe in you.",
  "Salamat sa dilig yah! Stay strong.",
  "Salamat sa dilig yah! Keep growing.",
  "Salamat sa dilig yah! Choose joy.",
  "Salamat sa dilig yah! Shine bright.",
  "Salamat sa dilig yah! Believe in you."
};

const int numAffirmations = sizeof(affirmations) / sizeof(affirmations[0]);

/*/////////////////////////////////////////////////////////////////////////////////////////////////////////
// --- GET AFFIRMATION MESSAGE STRING ---
/////////////////////////////////////////////////////////////////////////////////////////////////////////*/
String getAffirmationMessage() {
    int idx = random(numAffirmations);

    return String(affirmations[idx]);
}
