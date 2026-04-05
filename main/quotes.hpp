#ifndef QUOTES_HPP
#define QUOTES_HPP

#include <Arduino.h>
#include <Adafruit_SH110X.h>
#include "faceDisplay.hpp"

extern const int TIMEOUT_WIFI_CONNECT;
extern const char* wifiAPName;
extern const char* notConnectedMsg;
extern const char* apiUrl;

String fetchAndDisplayQuote(bool isConnected);
void initWifiConnection();

#endif // QUOTES_HPP