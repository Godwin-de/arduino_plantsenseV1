#ifndef BACKUPSYSTEMACCESS_HPP
#define BACKUPSYSTEMACCESS_HPP

// Save and load streak data
void saveStreakData();
void loadStreakData();
// Save and load current emotion
void SetSaveCurrentEmotion(int emotion);
int GetLoadCurrentEmotion();

#endif // BACKUPSYSTEMACCESS_HPP