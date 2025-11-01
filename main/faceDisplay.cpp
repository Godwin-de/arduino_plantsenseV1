#include "faceDisplay.hpp"

/*/////////////////////////////////////////////////////////////////////////////////////////////////////////
// --- BASE FACE FUNCTION ---
/////////////////////////////////////////////////////////////////////////////////////////////////////////*/
void drawVectorFace(int eyeHeight, int mouthHeight, int eyeOffset) {
    display.clearDisplay();

    // --- Eyes ---
    int leftEyeX = 38 + eyeOffset;
    int rightEyeX = 88 + eyeOffset;
    int eyeY = 25;
    int eyeWidth = 16;

    display.fillRoundRect(leftEyeX - eyeWidth / 2, eyeY - eyeHeight / 2, eyeWidth, eyeHeight, 4, SH110X_WHITE);
    display.fillRoundRect(rightEyeX - eyeWidth / 2, eyeY - eyeHeight / 2, eyeWidth, eyeHeight, 4, SH110X_WHITE);

    // --- Mouth ---
    int mouthY = 50;
    int mouthWidth = 40;
    int mouthX = (128 - mouthWidth) / 2 + (eyeOffset / 2); // subtle mouth shift

    display.fillRoundRect(mouthX, mouthY - mouthHeight / 2, mouthWidth, mouthHeight, 3, SH110X_WHITE);
    display.display();
}

/*/////////////////////////////////////////////////////////////////////////////////////////////////////////
// --- LOOK LEFT ---
/////////////////////////////////////////////////////////////////////////////////////////////////////////*/
void lookLeft(int eyeHeight, int mouthHeight) {
    drawVectorFace(eyeHeight, mouthHeight, -10);
}

/*/////////////////////////////////////////////////////////////////////////////////////////////////////////
// --- LOOK RIGHT ---
/////////////////////////////////////////////////////////////////////////////////////////////////////////*/
void lookRight(int eyeHeight, int mouthHeight) {
    drawVectorFace(eyeHeight, mouthHeight, 10);
}

/*/////////////////////////////////////////////////////////////////////////////////////////////////////////
// --- LOOK CENTER ---
/////////////////////////////////////////////////////////////////////////////////////////////////////////*/
void lookCenter(int eyeHeight, int mouthHeight) {
    drawVectorFace(eyeHeight, mouthHeight, 0);
}

/*/////////////////////////////////////////////////////////////////////////////////////////////////////////
// --- LOOK CENTER SEQUENCE ---
/////////////////////////////////////////////////////////////////////////////////////////////////////////*/
void lookCenterSequence() {
    // --- Normal blinking sequence ---
    lookCenter(20, 6); delay(1500);
    lookCenter(10, 6); delay(150);
    lookCenter(2, 6);  delay(120);
    lookCenter(10, 8); delay(150);
    lookCenter(20, 5); delay(1000);
}

/*/////////////////////////////////////////////////////////////////////////////////////////////////////////
// --- LOOK RIGHT SEQUENCE ---
/////////////////////////////////////////////////////////////////////////////////////////////////////////*/
void lookRightSequence() {
    // --- Look right with blink ---
    lookRight(20, 6); delay(1000);
    lookRight(10, 6); delay(150);
    lookRight(2, 6);  delay(100);
    lookRight(20, 6); delay(1000);

    Serial.println("Motion RIGHT detected!");
}

/*/////////////////////////////////////////////////////////////////////////////////////////////////////////
// --- LOOK LEFT SEQUENCE ---
/////////////////////////////////////////////////////////////////////////////////////////////////////////*/
void lookLeftSequence() {
    // --- Look left with blink ---
    lookLeft(20, 6); delay(1000);
    lookLeft(10, 6); delay(150);
    lookLeft(2, 6);  delay(100);
    lookLeft(20, 6); delay(1000);

    Serial.println("Motion LEFT detected!");
}

/*/////////////////////////////////////////////////////////////////////////////////////////////////////////
// --- LOOK BOTH DIRECTION SEQUENCE ---
/////////////////////////////////////////////////////////////////////////////////////////////////////////*/
void lookBothDirSequence() {
    lookLeft(20, 6); delay(500);
    lookLeft(10, 6); delay(50);
    lookLeft(2, 6);  delay(25);
    lookLeft(20, 6); delay(500);

    lookRight(20, 6); delay(500);
    lookRight(10, 6); delay(50);
    lookRight(2, 6);  delay(25);
    lookRight(20, 6); delay(500);

    lookCenter(20, 6); delay(500);
    lookCenter(10, 6); delay(150);
    lookCenter(2, 6);  delay(1500);
    lookCenter(10, 8); delay(150);
    lookCenter(20, 5); delay(500);

    Serial.println("Motion BOTH DIRECTION detected!");
}

