#include <Preferences.h>
#include "engagementIndicator.hpp"   // for streakIndicator, happyStreak, etc.
#include "backupSystemAccess.hpp"

Preferences prefs;

/*/////////////////////////////////////////////////////////////////////////////////////////////////////////
// --- SAVE VALUES PERSISTENTLY / NON-VOLATILE ---
/////////////////////////////////////////////////////////////////////////////////////////////////////////*/
void saveStreakData() {
    // Initialize preferences namespace
    prefs.begin("PSStreakSystem", false); 

    // Save updated values persistently
    prefs.putInt("streakPoints", streakIndicator); 
    prefs.putInt("streakTierLevel", streakTierLevel);
    prefs.end();
}

/*/////////////////////////////////////////////////////////////////////////////////////////////////////////
// --- LOAD PERSISTENT DATA ---
/////////////////////////////////////////////////////////////////////////////////////////////////////////*/
void loadStreakData() {
    prefs.begin("PSStreakSystem", false);
    streakIndicator = prefs.getInt("streakPoints", 0); // load streak points, default 0 if not saved
    streakTierLevel = prefs.getInt("streakTierLevel", 0); // load streak tier level, default 0 if not saved
    prefs.end();
}