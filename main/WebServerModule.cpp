#include <Arduino.h>
#include "WebServerModule.h"
#include "WifiManager.h"

WebServer server(80);

// Declare handler functions
void handleRoot(){
  Serial.println("Root Route");
  const char* htmlContent = R"rawliteral(
    <!DOCTYPE html><html><head><meta charset="UTF-8" /><meta name="viewport" content="width=device-width" /><title>Smart Switch | Qsense</title>
    </head><style>*{margin:0;padding:0;box-sizing:border-box;}html,body{width:100vw;height:100vh;font-family:sans-serif;background-color:#f0f0f0;overflow:hidden;display:flex;flex-direction:column;justify-content:center;align-items:center;}.container{width:calc(100% - 40px);max-width:600px;padding:20px;background-color:#ffffff;border-radius:15px;display:flex;flex-direction:column;justify-content:space-around;align-items:center;gap:40px;}h1,h3,p{text-align:center;}h1{font-size:3rem;color:#232323;}
    h3{font-size:1.4rem;}p{margin:20px auto;}form{width:100%;}button{background-color:#4CAF50;border:none;border-radius:5px;color:#fff;cursor:pointer;display:block;font-size:1.2rem;margin:0 auto;padding:10px;width:100%;max-width:400px;}button:hover{background-color:#3e8e41;}
    </style><body><div class="container"><h1>Qsense</h1><div class="content"><h3>Lets Connect your Smart Switch</h3><p>We will guide you through the steps to connect the smart switch to your Wi-Fi network.</p></div>
    <form action="/scan" method="GET"><button>Begin</button></form></div></body>
    </html>)rawliteral";

  server.send(200, "text/html", htmlContent);
}

void getWiFi(){
  Serial.println("WiFi Scan Route");
  
  // Scans the network
  const int maxSize = 20; 
  String networks[maxSize];
  
  int totalNetworks = scanWiFiNetworks(networks);

  // Start JSON string
  String jsonResponse = "{\"totalNetworks\": " + String(totalNetworks) + ",\"networks\": [";

  // Add networks to JSON
  for (int i = 0; i < totalNetworks; ++i) {
    jsonResponse += "\"" + networks[i] + "\"";
    if (i < totalNetworks - 1) {
      jsonResponse += ", "; // Add comma between networks
    }
  }

  jsonResponse += "]}"; // Close JSON string

  server.send(200, "application/json", jsonResponse);
}

void handleWiFiScan(){

  const char* htmlContent = R"rawliteral(<!DOCTYPE html>
<html>
<head>
    <meta charset="UTF-8" />
    <meta name="viewport" content="width=device-width" />
    <title>Smart Switch | Qsense</title>
</head>
<style>
    *{
        margin: 0;
        padding: 0;
        box-sizing: border-box;
    }
    html,   
    body {
        width: 100vw;
        height: 100vh;
        font-family: sans-serif;
        background-color: #f0f0f0;
        overflow: hidden;
        display: flex;
        flex-direction: column;
        justify-content: center;
        align-items: center;
    }
    .container {
        width: calc(100% - 40px);
        max-width: 600px;
        padding: 20px;
        background-color: #ffffff;
        border-radius: 15px;
        display: flex;
        flex-direction: column;
        justify-content: space-around;
        align-items: center;
    }
   
    h1,h3{
        text-align: center;
    }
   
     h1{
        font-size: 3rem;
        color: #232323;
        margin-bottom: 40px;
    }
    form{
        width: 100%;
    }
    select,input{
        width: 100%;
        font-size: 1rem;
        padding: 10px 5px;
        border: 1px solid #ccc;
        border-radius: 5px;
        margin: 10px auto 20px;
    }

    select:focus,input:focus{
        outline: none;
        border-color: #4CAF50;
    }
    button {
        background-color: #4c99af;
        border: none;
        border-radius: 5px;
        color: #fff;
        cursor: pointer;
        display: block;
        font-size: 1.2rem;
        margin: 10px auto 0;
        padding: 10px;
        width: 100%;
        max-width: 400px;
    }
    button:hover {
        background-color: #377789;
    }
    button:last-child{
        background-color: #4CAF50;
    }
    button:last-child:hover{
        background-color: #3e8e41;
    }
    .loader {
  color: #4CAF50;
  font-size: 40px;
  text-indent: -9999em;
  overflow: hidden;
  width: 1em;
  height: 1em;
  border-radius: 50%;
  margin: 72px auto;
  position: relative;
  -webkit-transform: translateZ(0);
  -ms-transform: translateZ(0);
  transform: translateZ(0);
  -webkit-animation: load6 1.7s infinite ease, round 1.7s infinite ease;
  animation: load6 1.7s infinite ease, round 1.7s infinite ease;
}
@-webkit-keyframes load6 {
  0% {
    box-shadow: 0 -0.83em 0 -0.4em, 0 -0.83em 0 -0.42em, 0 -0.83em 0 -0.44em, 0 -0.83em 0 -0.46em, 0 -0.83em 0 -0.477em;
  }
  5%,
  95% {
    box-shadow: 0 -0.83em 0 -0.4em, 0 -0.83em 0 -0.42em, 0 -0.83em 0 -0.44em, 0 -0.83em 0 -0.46em, 0 -0.83em 0 -0.477em;
  }
  10%,
  59% {
    box-shadow: 0 -0.83em 0 -0.4em, -0.087em -0.825em 0 -0.42em, -0.173em -0.812em 0 -0.44em, -0.256em -0.789em 0 -0.46em, -0.297em -0.775em 0 -0.477em;
  }
  20% {
    box-shadow: 0 -0.83em 0 -0.4em, -0.338em -0.758em 0 -0.42em, -0.555em -0.617em 0 -0.44em, -0.671em -0.488em 0 -0.46em, -0.749em -0.34em 0 -0.477em;
  }
  38% {
    box-shadow: 0 -0.83em 0 -0.4em, -0.377em -0.74em 0 -0.42em, -0.645em -0.522em 0 -0.44em, -0.775em -0.297em 0 -0.46em, -0.82em -0.09em 0 -0.477em;
  }
  100% {
    box-shadow: 0 -0.83em 0 -0.4em, 0 -0.83em 0 -0.42em, 0 -0.83em 0 -0.44em, 0 -0.83em 0 -0.46em, 0 -0.83em 0 -0.477em;
  }
}
@keyframes load6 {
  0% {
    box-shadow: 0 -0.83em 0 -0.4em, 0 -0.83em 0 -0.42em, 0 -0.83em 0 -0.44em, 0 -0.83em 0 -0.46em, 0 -0.83em 0 -0.477em;
  }
  5%,
  95% {
    box-shadow: 0 -0.83em 0 -0.4em, 0 -0.83em 0 -0.42em, 0 -0.83em 0 -0.44em, 0 -0.83em 0 -0.46em, 0 -0.83em 0 -0.477em;
  }
  10%,
  59% {
    box-shadow: 0 -0.83em 0 -0.4em, -0.087em -0.825em 0 -0.42em, -0.173em -0.812em 0 -0.44em, -0.256em -0.789em 0 -0.46em, -0.297em -0.775em 0 -0.477em;
  }
  20% {
    box-shadow: 0 -0.83em 0 -0.4em, -0.338em -0.758em 0 -0.42em, -0.555em -0.617em 0 -0.44em, -0.671em -0.488em 0 -0.46em, -0.749em -0.34em 0 -0.477em;
  }
  38% {
    box-shadow: 0 -0.83em 0 -0.4em, -0.377em -0.74em 0 -0.42em, -0.645em -0.522em 0 -0.44em, -0.775em -0.297em 0 -0.46em, -0.82em -0.09em 0 -0.477em;
  }
  100% {
    box-shadow: 0 -0.83em 0 -0.4em, 0 -0.83em 0 -0.42em, 0 -0.83em 0 -0.44em, 0 -0.83em 0 -0.46em, 0 -0.83em 0 -0.477em;
  }
}
@-webkit-keyframes round {
  0% {
    -webkit-transform: rotate(0deg);
    transform: rotate(0deg);
  }
  100% {
    -webkit-transform: rotate(360deg);
    transform: rotate(360deg);
  }
}
@keyframes round {
  0% {
    -webkit-transform: rotate(0deg);
    transform: rotate(0deg);
  }
  100% {
    -webkit-transform: rotate(360deg);
    transform: rotate(360deg);
  }
}

</style>
<script>
    function getWiFiNetworks() {
        var xhr = new XMLHttpRequest();
        xhr.onreadystatechange = function () {
            if (this.readyState == 4 && this.status == 200) {
                // Parse the JSON response
                var response = JSON.parse(this.responseText);

                // Create options for the select element
                var options = response.networks.map(function (network) {
                    return '<option value="' + network + '">' + network + '</option>';
                }).join('');

                // Replace the spinner with the Wi-Fi networks form
                document.querySelector('.content').innerHTML = `
                <h4>Choose Wi-Fi network your device will use</h4>
                <form action="/connect" method="POST">
                    <select name="ssid" id="ssid">${options}</select>
                    <input type="password" name="password" id="password" placeholder="Password">
                    <button type="button" onClick="scan()">Rescan</button>
                    <button type="button" onClick="connect()">Continue</button>
                </form>
                `;
            }
        };
        xhr.open("GET", "/getWifi", true);
        xhr.send();
    }

    function scan() {
        document.querySelector('.content').innerHTML = `<h4>Scanning Wi-Fi Networks...</h4>
            <div class="loader">Loading...</div>`;

        getWiFiNetworks();
    }
    function connect(){
        let ssid = document.querySelector('#ssid').value;
        let password = document.querySelector('#password').value;
        
        console.log("ssid", ssid);
        console.log("password", password)

        document.querySelector('.content').innerHTML = `<h4>Connecting to ${ssid}...</h4>
            <div class="loader">Loading...</div>`;

             var xhr = new XMLHttpRequest();
        xhr.onreadystatechange = function () {
            if (this.readyState == 4) {
                // Check if the request was successful
                if (this.status == 200) {
                    var response = JSON.parse(this.responseText);
                    // Check the connection status and respond accordingly
                    if (response.status === 'connected') {
                        alert("Successfully connected to Wi-Fi network.");
                        // Additional actions on successful connection
                    } else {
                        alert("Failed to connect to Wi-Fi network.");
                        // Additional actions on failure to connect
                        scan()
                    }
                } else {
                    // Handle HTTP error
                    alert("Error connecting to the Wi-Fi network.");
                    scan();
                }
            }
        };
        xhr.open("POST", "/connect", true);
        xhr.setRequestHeader("Content-type", "application/x-www-form-urlencoded");
        xhr.send("ssid=" + encodeURIComponent(ssid) + "&password=" + encodeURIComponent(password));
    }

    // Initial call
    getWiFiNetworks();
</script>

<body>
    <div class="container">
    
        <h1>Qsense</h1>
   
        <div class="content">
            <h4>Scanning Wi-Fi Networks...</h4>
            <div class="loader">Loading...</div>
        </div>
    </div>
</body>
</html>)rawliteral";

  server.send(200, "text/html", htmlContent);
}

void handleWiFiConnect(){
  Serial.println("WiFi Connect Route");

  if (server.hasArg("ssid") && server.hasArg("password")) {
        String ssid = server.arg("ssid");
        String password = server.arg("password");

        Serial.println("SSID: " + ssid);
        Serial.println("Password: " + password);
  
        bool result = connectWiFi(ssid, password);
        String jsonResponse;

        if(result)
          jsonResponse = "{\"status\":\"connected\"}";
        else
          jsonResponse ="{\"status\":\"disconnected\"}";

        server.send(200, "application/json",jsonResponse);
    }
    else {
        // If ssid or password is missing, send an error message
        server.send(400, "application/json", "{\"status\":\"missing ssid or password\"}");
    }   
}

void handleNotFound(){
  Serial.println("Not Found : 404");
  server.send(404,"text/plain","404: Not Found");
}

// Declare List of Web routes
void WebRoutes(){
  server.on("/", HTTP_GET, handleRoot);
  server.on("/scan", HTTP_GET, handleWiFiScan);
  server.on("/getWifi", HTTP_GET, getWiFi);
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


