#ifndef FACEDISPLAY_HPP
#define FACEDISPLAY_HPP

#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>

// Make the display object in main.ino visible to cpp
extern Adafruit_SH1106G display;

void drawVectorFace(int eyeHeight, int mouthHeight, int eyeOffset = 0);
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

// Text display
void displayAffirmationMessage(const char* message);

// Checker
void showEmotion(int soilMoisturePercent);

// Others
int getCurrentEmotion();

// variables
enum EmotionState {
  HAPPY,
  NEUTRAL,
  SAD
};

extern int currentEmotion;


#endif
