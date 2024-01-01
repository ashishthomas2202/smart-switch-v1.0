#ifndef WiFiManager_h
#define WiFiManager_h

#include "Config.h"
#include <WiFi.h>

void setupWiFiManager();
void startAccessPoint();
void stopAccessPoint();
void handleAP();

int scanWiFiNetworks(String*);
bool connectWiFi(const String& ssid, const String& password);

void setupWiFi();
void handleWiFi();

#endif