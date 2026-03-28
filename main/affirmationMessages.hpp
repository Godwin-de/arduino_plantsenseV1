#ifndef AFFIRMATIONMESSAGES_HPP
#define AFFIRMATIONMESSAGES_HPP

struct TimeStamp {
  int hour;
  int minute;
  int second;
  const char* message;
};

extern TimeStamp timelyReminders[];
extern const int numTimelyReminders;
extern const char* affirmations[];
extern const int numAffirmations;


String getAffirmationMessage();


#endif