#include "engagementIndicator.hpp"
#include "faceDisplay.hpp"
#include "backupSystemAccess.hpp"

#define STREAK_TIER_UNLOCK 15
#define STREAK_TIER_LEVEL_MAX 4
int streakIndicator = 0;
int streakTierLevel = 0;

/*/////////////////////////////////////////////////////////////////////////////////////////////////////////
// --- UPDATE ENGAGEMENT STREAK POINTS ---
/////////////////////////////////////////////////////////////////////////////////////////////////////////*/
void updateEngagementStreak(int currentEmotion) {
    // Add current emotion to the streak system
    switch (currentEmotion)
    {
        case HAPPY:
        {
            streakIndicator += 3; // Increase streak indicator by 3 for happy emotion
            break;
        }
        case NEUTRAL:
        {
            streakIndicator += 1; // Increase streak indicator by 1 for neutral emotion
            break;
        }
        case SAD:
        { 
            streakIndicator = 0; // Reset streak points for sad emotion
            // temp TODO - reset if 24 has already passed
            break;
        }
        
        default:    break;
    }

    saveStreakData();
}

/*/////////////////////////////////////////////////////////////////////////////////////////////////////////
// --- UPDATE ENGAGEMENT STREAK TIER LEVEL ---
/////////////////////////////////////////////////////////////////////////////////////////////////////////*/
void updateUnlockTierLevelStreak(int currentStreakPoints) {
    if(currentStreakPoints >= STREAK_TIER_UNLOCK) {
        // Unlock new tier level
        streakTierLevel++;
        streakIndicator = 0;

        if(streakTierLevel >= STREAK_TIER_LEVEL_MAX) {
            // streakTierLevel = STREAK_TIER_LEVEL_MAX; // Tier level at max
            streakTierLevel = 0; // For testing purposes, reset tier level back to 0 after reaching max
        }

        // temp TODO - add different face display unlocks for each tier level
        if(streakTierLevel == 1) {
            Serial.println("LEVEL 1: New face display unlocked: Smiley Face! 😊");
        }
        else if (streakTierLevel == 2) {
            Serial.println("LEVEL 2: New face display unlocked: Party Face! 🥳");
        }
        else if (streakTierLevel == 3) {
            Serial.println("LEVEL 3: New face display unlocked: Starry-Eyed Face! 🤩");
        }
        else {
            Serial.println("You've reached the maximum streak tier level! Keep up the great work! 🌟");
        }
    }

    saveStreakData();
}

/*/////////////////////////////////////////////////////////////////////////////////////////////////////////
// --- GET ENGAGEMENT STREAK POINTS ---
/////////////////////////////////////////////////////////////////////////////////////////////////////////*/
int getCurrentStreakValues() {
    return streakIndicator;
}