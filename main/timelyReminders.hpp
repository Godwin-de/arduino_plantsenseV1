#ifndef TIMELYREMINDERS_HPP
#define TIMELYREMINDERS_HPP

struct Affirmation {
  int hour;
  int minute;
  int second;
  const char* message;
};

// Define your daily affirmations here
Affirmation timelyReminders[] = {
  {3, 10, 0, "🌞 Good morning! Stay positive today."},
  {3, 13, 0, "🍴 Lunchtime reminder: nourish yourself well."},
  {3, 15, 0, "🌇 Evening check-in: you did great today."},
  {3, 20, 0, "🌙 Wind down, tomorrow is another chance."}
};

const int numAffirmations = sizeof(timelyReminders) / sizeof(timelyReminders[0]);


#endif