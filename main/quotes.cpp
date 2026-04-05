#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "quotes.hpp"
#include <WiFiManager.h>


// WiFi connection parameters
const int TIMEOUT_WIFI_CONNECT = 10; // 1 minute

// WiFi credentials
const char* wifiAPName = "SSID:PlantSense";
const char* notConnectedMsg = "NO QUOTE";

// Your Railway API URL
const char* apiUrl = "https://quote-api-production-6c28.up.railway.app/quote";

/*/////////////////////////////////////////////////////////////////////////////////////////////////////////
// --- DISPLAY AFFIRMATION MESSAGE WITH WATER REACTION FACE ---
/////////////////////////////////////////////////////////////////////////////////////////////////////////*/
String fetchAndDisplayQuote( bool isConnected ) {
    HTTPClient http;
    http.begin(apiUrl);
    http.addHeader("Content-Type", "application/json");
    int httpCode = http.GET();

    if (!isConnected) {
        http.end();
        return notConnectedMsg;
    }

    if (httpCode == 200) {
        String payload = http.getString();
        Serial.println("Response: " + payload);

        // Parse JSON
        DynamicJsonDocument doc(1024);
        deserializeJson(doc, payload);
        String quote = doc["quote"].as<String>();

        // Trim quote to fit 128x32 screen (max ~4 lines of text)
        if (quote.length() > 100) {
            quote = quote.substring(0, 97) + "...";
        }

        http.end();
        return quote;
    }
    else {
        http.end();
        return notConnectedMsg;
    }
}

/*/////////////////////////////////////////////////////////////////////////////////////////////////////////
// --- INITIALIZE WIFI CONNECTION ---
/////////////////////////////////////////////////////////////////////////////////////////////////////////*/
void initWifiConnection() {
    WiFiManager wm;
    wm.resetSettings();
    wm.setConfigPortalTimeout(TIMEOUT_WIFI_CONNECT);

    // Display instructions on the screen
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(SH110X_WHITE);
    display.setCursor(0,0);
    display.println("Configure WiFi:");
    display.println("1. Open WiFi settings\n");
    display.println("2. Connect to\nSSID:PlantSense\n");
    display.println("3. Click CONFIGURE in\ncaptive portal");
    display.display();
   
    // Portal call
    wm.autoConnect(wifiAPName);
}
