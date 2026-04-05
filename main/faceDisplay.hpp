#ifndef FACEDISPLAY_HPP
#define FACEDISPLAY_HPP

#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>

// Make the display object in main.ino visible to cpp
extern Adafruit_SH1106G display;

void drawVectorFace(int eyeHeight, int mouthHeight, int eyeOffset = 0, bool isFromSleep = false);
void lookLeft(int eyeHeight = 20, int mouthHeight = 6);
void lookRight(int eyeHeight = 20, int mouthHeight = 6);
void lookCenter(int eyeHeight = 20, int mouthHeight = 6);
void lookCenterSequence();
void lookRightSequence();
void lookLeftSequence();
void lookBothDirSequence();

// Emotions
void displayHappyEmo();
void displayNeutralEmo();
void displaySadEmo();
void displayWhistlingEmo();
void displayWinkingSequence();
void displayBreathingCalmSequence();
void displayLoveEmoteSequence();


// Text display
void displayAffirmationMessage(const char* message);
void displayWifiLoadingAnimation(int cycles, int delayMs);
void displayWifiConnectionStatus(bool isConnected);

// Checker
void showEmotion(int soilMoisturePercent);

// Others
int getCurrentEmotion();
void displayCenteredText(const char* text, int cursorY = -1);
void displayWrappedText(const char* text);


// variables
enum EmotionState {
  HAPPY,
  NEUTRAL,
  SAD
};

extern int currentEmotion;


#endif
