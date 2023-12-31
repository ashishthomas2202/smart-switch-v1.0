#include <Arduino.h>
#include "SystemStates.h"
#include "WifiManager.h"
#include "WebServerModule.h"
// not using
void setupWiFiManager(){
  startAccessPoint();
}

void startAccessPoint(){
  WiFi.mode(WIFI_AP_STA);
  
  #ifdef AP_OPEN
    WiFi.softAP(AP_SSID);
    Serial.println("Open Access Point started.");
  #else
    WiFi.softAP(AP_SSID, AP_PASSWORD);
    Serial.println("Access Point started.");
  #endif

  Serial.println("IP address: ");
  Serial.println(WiFi.softAPIP());

  startWebServer();
}

void stopAccessPoint(){

  stopWebServer();

  WiFi.softAPdisconnect(true);
  Serial.println("Access Point stopped");
}

void handleAP(){
  // handleWebServer();
  switch(systemState){
    case SystemState::UNINITIALIZED:
      startAccessPoint();
      systemState = SystemState::AP_MODE;
      break;
    case SystemState::AP_MODE:
      handleWebServer(); 
      break;
  }
}

