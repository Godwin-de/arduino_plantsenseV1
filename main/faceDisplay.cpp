#include "faceDisplay.hpp"
#include "backupSystemAccess.hpp"

int currentEmotion = 0;

/*/////////////////////////////////////////////////////////////////////////////////////////////////////////
// --- BASE FACE FUNCTION ---
/////////////////////////////////////////////////////////////////////////////////////////////////////////*/
void drawVectorFace(int eyeHeight, int mouthHeight, int eyeOffset, bool isFromSleep ) {
    display.clearDisplay();

    currentEmotion = GetLoadCurrentEmotion(); // Load the saved emotion

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

    if(isFromSleep) {
        display.fillRoundRect(mouthX, mouthY - mouthHeight / 2, mouthWidth, mouthHeight, 3, SH110X_WHITE);
    } else if(currentEmotion == HAPPY) {
        // Happy mouth (curved smile)
        for (int i = 0; i < 4; i++) {
            display.drawLine(mouthX, mouthY + i, mouthX + 10, mouthY + mouthHeight + i, SH110X_WHITE);
            display.drawLine(mouthX + 10, mouthY + mouthHeight + i, mouthX + 30, mouthY + mouthHeight + i, SH110X_WHITE);
            display.drawLine(mouthX + 30, mouthY + mouthHeight + i, mouthX + 40, mouthY + i, SH110X_WHITE);
        }
    } else if (currentEmotion == SAD) {
        // Sad mouth (curved frown)
        for (int i = 0; i < 4; i++) {
            display.drawLine(mouthX, mouthY + i, mouthX + 10, mouthY - mouthHeight + i, SH110X_WHITE);
            display.drawLine(mouthX + 10, mouthY - mouthHeight + i, mouthX + 30, mouthY - mouthHeight + i, SH110X_WHITE);
            display.drawLine(mouthX + 30, mouthY - mouthHeight + i, mouthX + 40, mouthY + i, SH110X_WHITE);
        }
    } else {
        display.fillRoundRect(mouthX, mouthY - mouthHeight / 2, mouthWidth, mouthHeight, 3, SH110X_WHITE);
    }

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

    // --- Eyes ---
    int eyeOffset = 0;       // adjust if you want shifting
    int eyeWidth = 16;
    int eyeHeight = 10;      // base height of eyes
    int leftEyeX = 38 + eyeOffset;
    int rightEyeX = 88 + eyeOffset;
    int eyeY = 25;

    // Draw full rounded eyes
    display.fillRoundRect(leftEyeX - eyeWidth / 2, eyeY - eyeHeight / 2, eyeWidth, eyeHeight, 4, SH110X_WHITE);
    display.fillRoundRect(rightEyeX - eyeWidth / 2, eyeY - eyeHeight / 2, eyeWidth, eyeHeight, 4, SH110X_WHITE);

    // Cut a portion at the upper side (mask with black rectangle)
    int cutHeight = 4;  // how much to trim from top
    display.fillRect(leftEyeX - eyeWidth / 2, eyeY - eyeHeight / 2, eyeWidth, cutHeight, SH110X_BLACK);
    display.fillRect(rightEyeX - eyeWidth / 2, eyeY - eyeHeight / 2, eyeWidth, cutHeight, SH110X_BLACK);

    // --- Mouth (shorter frown) ---
    int mouthHeight = 6;
    int mouthWidth = 28;   // shorter than happy
    int mouthY = 50;
    int mouthX = (128 - mouthWidth) / 2 + (eyeOffset / 2);

    display.fillRoundRect(mouthX, mouthY - mouthHeight / 2, mouthWidth, mouthHeight, 3, SH110X_WHITE);

    display.display();

    Serial.println("NEUTRAL LANG");
    delay(4000);
}

/*/////////////////////////////////////////////////////////////////////////////////////////////////////////
// --- SAD EMOTION ---
/////////////////////////////////////////////////////////////////////////////////////////////////////////*/
void displaySadEmo() {
    display.clearDisplay();

    int eyeOffset = 0;
    int eyeWidth = 16;
    int eyeHeight = 10;
    int leftEyeX = 38 + eyeOffset;
    int rightEyeX = 88 + eyeOffset;
    int eyeY = 25;

    // --- Eyes (base rounded rectangles) ---
    display.fillRoundRect(leftEyeX - eyeWidth / 2, eyeY - eyeHeight / 2, eyeWidth, eyeHeight, 4, SH110X_WHITE);
    display.fillRoundRect(rightEyeX - eyeWidth / 2, eyeY - eyeHeight / 2, eyeWidth, eyeHeight, 4, SH110X_WHITE);

    // --- Chip upper inner corners (mirrored diagonal cuts) ---
    int cutHeight = 4;  // how much to trim
    for (int i = 0; i < cutHeight; i++) {
        // Left eye: chip upper inner corner (slant inward)
        display.drawLine(leftEyeX, eyeY - eyeHeight / 2 - cutHeight + i,
                         leftEyeX - eyeWidth / 2, eyeY - eyeHeight / 2 + i, SH110X_BLACK);

        // Right eye: chip upper inner corner (mirrored slant inward)
        display.drawLine(rightEyeX, eyeY - eyeHeight / 2 - cutHeight + i,
                         rightEyeX + eyeWidth / 2, eyeY - eyeHeight / 2 + i, SH110X_BLACK);
    }

    // --- Curved Sad Mouth ---
    int mouthWidth = 40;
    int mouthY = 50;
    int mouthX = (128 - mouthWidth) / 2 + (eyeOffset / 2);

    for (int i = 0; i < 4; i++) {  // thickness
        display.drawLine(mouthX, mouthY + i, mouthX + 10, mouthY - 6 + i, SH110X_WHITE);
        display.drawLine(mouthX + 10, mouthY - 6 + i, mouthX + 30, mouthY - 6 + i, SH110X_WHITE);
        display.drawLine(mouthX + 30, mouthY - 6 + i, mouthX + 40, mouthY + i, SH110X_WHITE);
    }

    display.display();

    Serial.println("SAD YARN (mirrored chipped eyes + curved mouth)...");
    delay(4000);
}

/*/////////////////////////////////////////////////////////////////////////////////////////////////////////
// --- WHISTLING EMOTION SEQUENCE ---
/////////////////////////////////////////////////////////////////////////////////////////////////////////*/
void displayWhistlingEmo() {
    int mouthX = 64;   // center
    int mouthY = 48;
    int mouthRadius = 6;

    for (int frame = 0; frame < 6; frame++) {
        display.clearDisplay();

        // --- Eyes (slightly squinted) ---
        int leftEyeX = 38;
        int rightEyeX = 88;
        int eyeY = 25;
        int eyeWidth = 14;
        int eyeHeight = 6;

        display.fillRoundRect(leftEyeX - eyeWidth / 2, eyeY - eyeHeight / 2,
                              eyeWidth, eyeHeight, 3, SH110X_WHITE);
        display.fillRoundRect(rightEyeX - eyeWidth / 2, eyeY - eyeHeight / 2,
                              eyeWidth, eyeHeight, 3, SH110X_WHITE);

        // --- Mouth (puckered lips) ---
        // Animate radius slightly to simulate "whistle puff"
        int animRadius = mouthRadius + (frame % 2 == 0 ? 1 : -1);
        display.fillCircle(mouthX, mouthY, animRadius, SH110X_WHITE);

        // --- Musical note animation ---
        int noteX = mouthX + 10 + frame * 3;   // move right each frame
        int noteY = mouthY - 10 - frame;       // move upward each frame
        display.drawLine(noteX, noteY, noteX + 4, noteY - 4, SH110X_WHITE);
        display.drawLine(noteX + 4, noteY - 4, noteX + 6, noteY, SH110X_WHITE);

        display.display();
        delay(400); // frame delay
    }

    Serial.println("WHISTLING SEQUENCE PLAYED!");
}

/*/////////////////////////////////////////////////////////////////////////////////////////////////////////
// --- WINKING EMOTE SEQUENCE (5 seconds) ---
/////////////////////////////////////////////////////////////////////////////////////////////////////////*/
void displayWinkingSequence() {
    unsigned long startTime = millis();
    while (millis() - startTime < 5000) {  // run for 5 seconds
        // --- Frame 1: Normal happy face ---
        display.clearDisplay();
        int leftEyeX = 38;
        int rightEyeX = 88;
        int eyeY = 25;
        int eyeWidth = 16;
        int eyeHeight = 10;

        // Left eye open
        display.fillRoundRect(leftEyeX - eyeWidth / 2, eyeY - eyeHeight / 2,
                              eyeWidth, eyeHeight, 4, SH110X_WHITE);
        // Right eye open
        display.fillRoundRect(rightEyeX - eyeWidth / 2, eyeY - eyeHeight / 2,
                              eyeWidth, eyeHeight, 4, SH110X_WHITE);

        // Happy mouth
        int mouthX = 44;
        int mouthY = 50;
        for (int i = 0; i < 3; i++) {
            display.drawLine(mouthX, mouthY + i, mouthX + 10, mouthY + 6 + i, SH110X_WHITE);
            display.drawLine(mouthX + 10, mouthY + 6 + i, mouthX + 30, mouthY + 6 + i, SH110X_WHITE);
            display.drawLine(mouthX + 30, mouthY + 6 + i, mouthX + 40, mouthY + i, SH110X_WHITE);
        }
        display.display();
        delay(400);

        // --- Frame 2: Wink (right eye closed) ---
        display.clearDisplay();
        // Left eye open
        display.fillRoundRect(leftEyeX - eyeWidth / 2, eyeY - eyeHeight / 2,
                              eyeWidth, eyeHeight, 4, SH110X_WHITE);
        // Right eye closed (line instead of oval)
        display.drawLine(rightEyeX - 8, eyeY, rightEyeX + 8, eyeY, SH110X_WHITE);

        // Same happy mouth
        for (int i = 0; i < 3; i++) {
            display.drawLine(mouthX, mouthY + i, mouthX + 10, mouthY + 6 + i, SH110X_WHITE);
            display.drawLine(mouthX + 10, mouthY + 6 + i, mouthX + 30, mouthY + 6 + i, SH110X_WHITE);
            display.drawLine(mouthX + 30, mouthY + 6 + i, mouthX + 40, mouthY + i, SH110X_WHITE);
        }
        display.display();
        delay(400);
    }

    Serial.println("WINKING EMOTE SEQUENCE DONE!");
}

/*/////////////////////////////////////////////////////////////////////////////////////////////////////////
// --- BREATHING CALM EMOTE SEQUENCE (5 seconds) ---
/////////////////////////////////////////////////////////////////////////////////////////////////////////*/
void displayBreathingCalmSequence() {
    unsigned long startTime = millis();
    int duration = 5000; // total animation time
    int cycleTime = 2000; // one inhale + exhale cycle (2 seconds)
    
    while (millis() - startTime < duration) {
        int phase = (millis() - startTime) % cycleTime; // where we are in the cycle
        float progress = phase / (float)cycleTime;      // 0.0 → 1.0

        // Smooth breathing curve using sine wave
        float breath = (sin(progress * PI * 2 - PI/2) + 1) / 2; 
        // breath goes 0 → 1 → 0 smoothly

        display.clearDisplay();

        // --- Eyes (open/close smoothly) ---
        int leftEyeX = 38;
        int rightEyeX = 88;
        int eyeY = 25;
        int eyeWidth = 16;
        int eyeHeight = 4 + (int)(breath * 12); // eye height expands/contracts

        display.fillRoundRect(leftEyeX - eyeWidth/2, eyeY - eyeHeight/2,
                              eyeWidth, eyeHeight, 4, SH110X_WHITE);
        display.fillRoundRect(rightEyeX - eyeWidth/2, eyeY - eyeHeight/2,
                              eyeWidth, eyeHeight, 4, SH110X_WHITE);

        // --- Mouth (oval expands/contracts with breath) ---
        int mouthX = 64;
        int mouthY = 50;
        int mouthRadius = 4 + (int)(breath * 4); // mouth grows/shrinks

        display.drawCircle(mouthX, mouthY, mouthRadius, SH110X_WHITE);

        display.display();
        delay(50); // smooth frame rate
    }

    Serial.println("CALM BREATHING EMOTE DONE!");
}


/*/////////////////////////////////////////////////////////////////////////////////////////////////////////
// --- LOVE EMOTE SEQUENCE (Kiss + Heart Eyes, 5 seconds) ---
/////////////////////////////////////////////////////////////////////////////////////////////////////////*/
void displayLoveEmoteSequence() {
    unsigned long startTime = millis();
    while (millis() - startTime < 5000) {
        // --- Frame 1: Kiss Emote ---
        display.clearDisplay();

        // Eyes closed
        int leftEyeX = 38;
        int rightEyeX = 88;
        int eyeY = 25;
        display.drawLine(leftEyeX - 8, eyeY, leftEyeX + 8, eyeY, SH110X_WHITE);
        display.drawLine(rightEyeX - 8, eyeY, rightEyeX + 8, eyeY, SH110X_WHITE);

        // Puckered lips
        int mouthX = 64;
        int mouthY = 50;
        display.fillCircle(mouthX, mouthY, 6, SH110X_WHITE);

        // Heart drifting outward
        int offset = (millis() - startTime) / 400;
        int heartX = mouthX + 10 + offset * 3;
        int heartY = mouthY - 10 - offset * 2;
        display.drawLine(heartX, heartY, heartX + 3, heartY - 3, SH110X_WHITE);
        display.drawLine(heartX + 3, heartY - 3, heartX + 6, heartY, SH110X_WHITE);
        display.drawLine(heartX, heartY, heartX + 6, heartY, SH110X_WHITE);

        display.display();
        delay(400);

        // --- Frame 2: Heart Eyes Emote ---
        display.clearDisplay();

        // Heart eyes
        int size = 6;
        // Left heart
        display.drawLine(leftEyeX, eyeY, leftEyeX - size, eyeY - size, SH110X_WHITE);
        display.drawLine(leftEyeX, eyeY, leftEyeX + size, eyeY - size, SH110X_WHITE);
        display.drawLine(leftEyeX - size, eyeY - size, leftEyeX + size, eyeY - size, SH110X_WHITE);
        // Right heart
        display.drawLine(rightEyeX, eyeY, rightEyeX - size, eyeY - size, SH110X_WHITE);
        display.drawLine(rightEyeX, eyeY, rightEyeX + size, eyeY - size, SH110X_WHITE);
        display.drawLine(rightEyeX - size, eyeY - size, rightEyeX + size, eyeY - size, SH110X_WHITE);

        // Smiling mouth
        int mouthY2 = 50;
        int mouthX2 = 44;
        for (int i = 0; i < 3; i++) {
            display.drawLine(mouthX2, mouthY2 + i, mouthX2 + 10, mouthY2 + 6 + i, SH110X_WHITE);
            display.drawLine(mouthX2 + 10, mouthY2 + 6 + i, mouthX2 + 30, mouthY2 + 6 + i, SH110X_WHITE);
            display.drawLine(mouthX2 + 30, mouthY2 + 6 + i, mouthX2 + 40, mouthY2 + i, SH110X_WHITE);
        }

        display.display();
        delay(400);
    }

    Serial.println("LOVE EMOTE SEQUENCE DONE!");
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

    SetSaveCurrentEmotion(currentEmotion); // Save the current emotion persistently
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
    // SEQ3: Transition to happy face (closed eyes + shaded smile) ---
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
    // SEQ4: Show affirmation text ---
    display.clearDisplay();

    displayWrappedText(message); // scroll message across the screen

    display.display();
    delay(10000);
}

/*/////////////////////////////////////////////////////////////////////////////////////////////////////////
// --- DISPLAY WIFI LOADING ANIMATION ---
/////////////////////////////////////////////////////////////////////////////////////////////////////////*/
void displayWifiLoadingAnimation(int cycles, int delayMs) {
    const char* baseMsg = "Connecting to WiFi";

    for (int i = 1; i <= cycles; i++) {
        // Clear screen
        display.clearDisplay();
        display.setTextSize(1.5);
        display.setTextColor(SH110X_WHITE);

        // Build message with dots
        String msg = String(baseMsg);
        int dots = i % 4; // cycle through 0,1,2,3 dots
        for (int j = 0; j < dots; j++) {
            msg += ".";
        }

        displayCenteredText(msg.c_str());
        display.println(msg);
        display.display();

        delay(delayMs);
    }
}

/*/////////////////////////////////////////////////////////////////////////////////////////////////////////
// --- DISPLAY AFFIRMATION MESSAGE WITH WATER REACTION FACE ---
/////////////////////////////////////////////////////////////////////////////////////////////////////////*/
void displayWifiConnectionStatus(bool isConnected) {
    display.clearDisplay();
    display.setTextSize(1.5);
    display.setTextColor(SH110X_WHITE);

    const char* msg;
    if (isConnected) {
        msg = "WiFi Connected!";
        Serial.println("WiFi connected!");
    } else {
        msg = "Connection Failed!";
        Serial.println("WiFi connection failed. Proceeding without API.");
    }

    displayCenteredText(msg);
    display.print(msg);

    display.display();
    delay(3000);
}

/*/////////////////////////////////////////////////////////////////////////////////////////////////////////
// --- DISPLAY CENTERED TEXT ---
/////////////////////////////////////////////////////////////////////////////////////////////////////////*/
void displayCenteredText(const char* text, int cursorY) {
    // Measure text bounds
    int16_t x, y;
    uint16_t w, h;
    display.getTextBounds(text, 0, 0, &x, &y, &w, &h);

    // Center horizontally and vertically
    int centerX = (display.width() - w) / 2 - x;
    if (cursorY == -1) {
        cursorY = (display.height() - h) / 2 - y; // vertical center if not specified
    }

    display.setCursor(centerX, cursorY);
}

/*/////////////////////////////////////////////////////////////////////////////////////////////////////////
// --- DISPLAY WRAPPED TEXT (NO WORD CUTTING) ---
/////////////////////////////////////////////////////////////////////////////////////////////////////////*/
void displayWrappedText(const char* text) {
    String msg(text);
    int16_t x, y;
    uint16_t w, h;

    int cursorY = 0;
    int start = 0;
    String line = "";

    // Measure line height using a sample character
    display.getTextBounds("A", 0, 0, &x, &y, &w, &h);
    int lineHeight = h + 2;

    // Adjust usable width (leave a margin of 4 pixels on each side)
    int usableWidth = display.width() - 8;

    while (start < msg.length()) {
        int spaceIndex = msg.indexOf(' ', start);
        if (spaceIndex == -1) spaceIndex = msg.length();
        String word = msg.substring(start, spaceIndex);

        // Test if adding this word fits
        String testLine = line.length() > 0 ? line + " " + word : word;
        display.getTextBounds(testLine.c_str(), 0, 0, &x, &y, &w, &h);

        if (w > usableWidth) {
            // Print current line
            display.setCursor(0, cursorY);
            display.print(line);

            // Move to next line
            cursorY += lineHeight;
            line = word;
        } else {
            line = testLine;
        }

        start = spaceIndex + 1;
    }

    // Print the last line
    if (line.length() > 0) {
        display.setCursor(0, cursorY);
        display.print(line);
    }
}




