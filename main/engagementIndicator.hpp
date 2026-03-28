#ifndef ENGAGEMENTINDICATOR_HPP
#define ENGAGEMENTINDICATOR_HPP

void saveStreakData();
void loadStreakData();
void updateEngagementStreak(int currentEmotion);
void updateUnlockTierLevelStreak(int currentStreakPoints);
int getCurrentStreakValues();

extern int streakIndicator;
extern int streakTierLevel;


#endif // ENGAGEMENTINDICATOR_HPP