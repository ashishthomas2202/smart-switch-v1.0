// #include "SystemStates.h"
#include "WiFiManager.h"
#include "SwitchModule.h"

void setup() {
  Serial.begin(115200);
}

void loop() {
  handleSwitch();
  handleAP();
  delay(1000);
}
