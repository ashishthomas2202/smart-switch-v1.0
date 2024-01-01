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

int scanWiFiNetworks(String* networkNames){

  int n = WiFi.scanNetworks();
  Serial.println("Scan Done");
  
  if(n == 0){
    Serial.println("No Networks Found");
  }
  else{
    Serial.print(n);
    Serial.println(" Networks Found");
    Serial.println("Nr | SSID                             | RSSI | CH | Encryption");
    for (int i = 0; i < n; ++i) {
            
      networkNames[i] = WiFi.SSID(i);

      // Print SSID and RSSI for each network found
      Serial.printf("%2d",i + 1);
      Serial.print(" | ");
      Serial.printf("%-32.32s", WiFi.SSID(i).c_str());
      Serial.print(" | ");
      Serial.printf("%4d", WiFi.RSSI(i));
      Serial.print(" | ");
      Serial.printf("%2d", WiFi.channel(i));
      Serial.print(" | ");
      
      switch (WiFi.encryptionType(i)){
        case WIFI_AUTH_OPEN:
              Serial.print("open");
              break;
        case WIFI_AUTH_WEP:
              Serial.print("WEP");
              break;
        case WIFI_AUTH_WPA_PSK:
              Serial.print("WPA");
              break;
        case WIFI_AUTH_WPA2_PSK:
              Serial.print("WPA2");
              break;
        case WIFI_AUTH_WPA_WPA2_PSK:
              Serial.print("WPA+WPA2");
              break;
        case WIFI_AUTH_WPA2_ENTERPRISE:
              Serial.print("WPA2-EAP");
              break;
        case WIFI_AUTH_WPA3_PSK:
              Serial.print("WPA3");
              break;
        case WIFI_AUTH_WPA2_WPA3_PSK:
              Serial.print("WPA2+WPA3");
              break;
        case WIFI_AUTH_WAPI_PSK:
              Serial.print("WAPI");
              break;
        default:
              Serial.print("unknown");
      }
      Serial.println();
      delay(10);
    }
    
    Serial.println("");

    // int status = WiFi.scanComplete();
    // if(status == WIFI_SCAN_RUNNING)
    //   Serial.println("WiFi Scan Running...");
    // else if(status == WIFI_SCAN_FAILED)
    //   Serial.println("WiFi Scan Failed...");
    // else
    //   Serial.println("WiFi Scan Complete...");

    // Delete the scan result to free memory for code below.
    WiFi.scanDelete();

    return n;
  }

}

bool connectWiFi(const String& ssid,const String& password){

  Serial.println("Trying to connect WiFi...");
  Serial.println("ssid: " + ssid);
  Serial.println("password: " + password);

  WiFi.begin(ssid.c_str(), password.c_str());

    // Try to connect multiple times
    for (int i = 0; i < 5; i++) {
      Serial.println("connecting...(" +  String( i+1 ) + ")" + String(WiFi.status()));
        if (WiFi.status() == WL_CONNECTED) {
            Serial.println("Connected to " + ssid);
            return true;  // Successfully connected
        }
        delay(2000);  // Wait for 2 seconds before trying again
        //WiFi.mode(WIFI_AP_STA);  // Reset to AP_STA mode
    }

    WiFi.disconnect();
    Serial.println("Unable to connect to WiFi");
    return false;  // Connection failed after multiple attempts
}
