#ifndef WiFiManager_h
#define WiFiManager_h

#include "Config.h"
#include <WiFi.h>

void setupWiFiManager();
void startAccessPoint();
void stopAccessPoint();
void handleAP();

void setupWiFi();
void handleWiFi();

#endif