#include "faceDisplay.hpp"

int currentEmotion = 0;

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

/*/////////////////////////////////////////////////////////////////////////////////////////////////////////
// --- NEUTRAL EMOTION ---
/////////////////////////////////////////////////////////////////////////////////////////////////////////*/
void displayNeutralEmo() {
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

    Serial.println("NEUTRAL LANG!");
    delay(4000);
}

/*/////////////////////////////////////////////////////////////////////////////////////////////////////////
// --- SAD EMOTION ---
/////////////////////////////////////////////////////////////////////////////////////////////////////////*/
void displaySadEmo() {
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

    Serial.println("SAD YARN!");
    delay(4000);
}

/*/////////////////////////////////////////////////////////////////////////////////////////////////////////
// --- DETERMINE EMOTION BASED ON SOIL MOISTURE PERCENTAGE ---
/////////////////////////////////////////////////////////////////////////////////////////////////////////*/
void showEmotion(int soilMoisturePercent) {
    if (soilMoisturePercent >= 67) {
        displayHappyEmo();
        currentEmotion = HAPPY;
    }
    else if (soilMoisturePercent <= 32) {
        displaySadEmo(); // Implement this function for a sad expression
        currentEmotion = SAD;
    }
    else {
        displayNeutralEmo(); // Implement this function for a neutral expression
        currentEmotion = NEUTRAL;
    }
}

/*/////////////////////////////////////////////////////////////////////////////////////////////////////////
// --- GET CURRENT EMOTION ---
/////////////////////////////////////////////////////////////////////////////////////////////////////////*/
int getCurrentEmotion() {
    return currentEmotion;
}

/*/////////////////////////////////////////////////////////////////////////////////////////////////////////
// --- DISPLAY AFFIRMATION MESSAGE WITH WATER REACTION FACE ---
/////////////////////////////////////////////////////////////////////////////////////////////////////////*/
void displayAffirmationMessage(const char* message) {
    display.clearDisplay();

    int leftEyeX = 38;
    int rightEyeX = 88;
    int eyeY = 20;

    ////////////////////////////////////////////////////////
    // SEQ1: Shocked face (big round eyes + open mouth) ---
    display.fillCircle(leftEyeX, eyeY, 6, SH110X_WHITE);    // left eye wide open
    display.fillCircle(rightEyeX, eyeY, 6, SH110X_WHITE);   // right eye wide open
    display.fillCircle(64, 42, 10, SH110X_WHITE);           // shaded open mouth
    display.display();
    delay(1000);

    ////////////////////////////////////////////////////////
    // SEQ2: Shocked face (curved eyes + open mouthe) ---
    display.clearDisplay();

    for (int i = 0; i < 4; i++) {
        // Left eye curve
        display.drawLine(leftEyeX - 7, eyeY + i, leftEyeX - 3, eyeY - 2 + i, SH110X_WHITE);
        display.drawLine(leftEyeX - 3, eyeY - 2 + i, leftEyeX + 3, eyeY - 2 + i, SH110X_WHITE);
        display.drawLine(leftEyeX + 3, eyeY - 2 + i, leftEyeX + 7, eyeY + i, SH110X_WHITE);

        // Right eye curve
        display.drawLine(rightEyeX - 7, eyeY + i, rightEyeX - 3, eyeY - 2 + i, SH110X_WHITE);
        display.drawLine(rightEyeX - 3, eyeY - 2 + i, rightEyeX + 3, eyeY - 2 + i, SH110X_WHITE);
        display.drawLine(rightEyeX + 3, eyeY - 2 + i, rightEyeX + 7, eyeY + i, SH110X_WHITE);
    }

    display.fillCircle(64, 42, 10, SH110X_WHITE); // shaded open mouth
    display.display();
    delay(700);

    ////////////////////////////////////////////////////////
    // SEQ2: Transition to happy face (closed eyes + shaded smile) ---
    display.clearDisplay();

    // Closed/smiling eyes (curves instead of circles)
    for (int i = 0; i < 4; i++) {
        // Left eye curve
        display.drawLine(leftEyeX - 7, eyeY + i, leftEyeX - 3, eyeY - 2 + i, SH110X_WHITE);
        display.drawLine(leftEyeX - 3, eyeY - 2 + i, leftEyeX + 3, eyeY - 2 + i, SH110X_WHITE);
        display.drawLine(leftEyeX + 3, eyeY - 2 + i, leftEyeX + 7, eyeY + i, SH110X_WHITE);

        // Right eye curve
        display.drawLine(rightEyeX - 7, eyeY + i, rightEyeX - 3, eyeY - 2 + i, SH110X_WHITE);
        display.drawLine(rightEyeX - 3, eyeY - 2 + i, rightEyeX + 3, eyeY - 2 + i, SH110X_WHITE);
        display.drawLine(rightEyeX + 3, eyeY - 2 + i, rightEyeX + 7, eyeY + i, SH110X_WHITE);
    }

    // Smiling mouth (shaded curve)
    int mouthWidth = 40;
    int mouthY = 42;
    int mouthX = (128 - mouthWidth) / 2;
    display.fillRect(mouthX, mouthY, mouthWidth, 6, SH110X_WHITE); // shaded mouth block
    for (int i = 0; i < 4; i++) {
        display.drawLine(mouthX, mouthY + i, mouthX + 10, mouthY + 6 + i, SH110X_WHITE);
        display.drawLine(mouthX + 10, mouthY + 6 + i, mouthX + 30, mouthY + 6 + i, SH110X_WHITE);
        display.drawLine(mouthX + 30, mouthY + 6 + i, mouthX + 40, mouthY + i, SH110X_WHITE);
    }

    display.display();
    delay(2000);

    ////////////////////////////////////////////////////////
    // SEQ3: Show affirmation text ---
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(SH110X_WHITE);

    int16_t x, y;
    uint16_t w, h;
    display.getTextBounds(message, 0, 0, &x, &y, &w, &h);
    int centerX = (display.width() - w) / 2 - x;
    int centerY = 30;

    display.setCursor(centerX, centerY);
    display.print(message);

    display.display();
    delay(5000);
}














