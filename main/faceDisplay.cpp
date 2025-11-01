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

/*/////////////////////////////////////////////////////////////////////////////////////////////////////////
// --- HAPPY EMOTION ---
/////////////////////////////////////////////////////////////////////////////////////////////////////////*/
void displayHappyEmo() {
    display.clearDisplay();

    // --- Shifted upper center ---
    int leftEyeX = 38;
    int rightEyeX = 88;
    int eyeY = 20;  // moved eyes up
    int eyeWidth = 16;

    // Left eye curve (thicker by drawing multiple lines)
    for (int i = 0; i < 4; i++) {  // thickness: 4 pixels
        display.drawLine(leftEyeX - 7, eyeY + i, leftEyeX - 3, eyeY - 2 + i, SH110X_WHITE);
        display.drawLine(leftEyeX - 3, eyeY - 2 + i, leftEyeX + 3, eyeY - 2 + i, SH110X_WHITE);
        display.drawLine(leftEyeX + 3, eyeY - 2 + i, leftEyeX + 7, eyeY + i, SH110X_WHITE);
    }

    // Right eye curve
    for (int i = 0; i < 4; i++) {
        display.drawLine(rightEyeX - 7, eyeY + i, rightEyeX - 3, eyeY - 2 + i, SH110X_WHITE);
        display.drawLine(rightEyeX - 3, eyeY - 2 + i, rightEyeX + 3, eyeY - 2 + i, SH110X_WHITE);
        display.drawLine(rightEyeX + 3, eyeY - 2 + i, rightEyeX + 7, eyeY + i, SH110X_WHITE);
    }

    // --- Happy Mouth (thicker curved smile) ---
    int mouthWidth = 40;
    int mouthY = 42;  // moved mouth up
    int mouthX = (128 - mouthWidth) / 2;

    for (int i = 0; i < 4; i++) {  // thickness: 4 pixels
        display.drawLine(mouthX, mouthY + i, mouthX + 10, mouthY + 6 + i, SH110X_WHITE);
        display.drawLine(mouthX + 10, mouthY + 6 + i, mouthX + 30, mouthY + 6 + i, SH110X_WHITE);
        display.drawLine(mouthX + 30, mouthY + 6 + i, mouthX + 40, mouthY + i, SH110X_WHITE);
    }

    display.display();

    Serial.println("HAPPY YARN!");
    delay(4000);
}











