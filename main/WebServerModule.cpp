#include <Arduino.h>
#include "WebServerModule.h"

WebServer server(80);

// Declare handler functions
void handleRoot(){
  Serial.println("Root Route");
  // server.on("/", []() {
  //   if(!server.authenticate("admin","pass"){
  //     return server.requestAuthentication();
  //   }

  //   server.send(200, "text/plain", "Success");
  // });

  server.on("/", []() {
    if (!server.authenticate(WEBSERVER_USERNAME, WEBSERVER_PASSWORD)) {
      return server.requestAuthentication();
    }
    server.send(200, "text/plain", "Login OK");
  });
}

void handleWiFiScan(){
  Serial.println("WiFi Scan Route");
}

void handleWiFiConnect(){
  Serial.println("WiFi Connect Route");
}

void handleNotFound(){
  Serial.println("Not Found : 404");
  server.send(404,"text/plain","404: Not Found");
}

// Declare List of Web routes
void WebRoutes(){
  server.on("/", HTTP_GET, handleRoot);
  server.on("/scan", HTTP_GET, handleWiFiScan);
  server.on("/connect", HTTP_POST, handleWiFiConnect);
  server.onNotFound(handleNotFound);
}

void startWebServer(){

  WebRoutes(); // initialize all the routes
  server.begin();

  Serial.println("Web Server started");
  delay(2000);
}

void stopWebServer(){
  server.stop();
  Serial.println("Web Server stopped");
}

void handleWebServer(){
  server.handleClient();
}


