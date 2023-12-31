#ifndef WebServerModule_h
#define WebServerModule_h

#include <WebServer.h>

// const char* www_username = "admin";
// const char* www_password = "esp32";

#define WEBSERVER_USERNAME "admin"
#define WEBSERVER_PASSWORD "esp32"

void startWebServer();
void stopWebServer();
void handleWebServer();


// Declare List of Web routes
void WebRoutes();

// Declare handler functions
void handleRoot();
void handleWiFiScan();
void handleWiFiConnect();
void handleNotFound();

#endif