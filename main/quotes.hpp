#ifndef QUOTES_HPP
#define QUOTES_HPP

#include <Arduino.h>


extern const char* ssid;
extern const char* password;
extern const char* apiUrl;
extern const char* notConnectedMsg;

String fetchAndDisplayQuote(bool isConnected);

#endif // QUOTES_HPP