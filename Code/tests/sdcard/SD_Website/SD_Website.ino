#include "SDscript.h"
#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>

const char* ssid     = "testtest";
const char* password = "test1234";

WiFiServer server(80);

const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML><html>
<head>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <title>ESP32 Web Server</title>
  <style>
    html {font-family: Arial; display: inline-block; text-align: center;}
    h2 {font-size: 2.3rem;}
    h3 {font-size: 1.4rem; color: blue;}
    p {font-size: 1.9rem;}
    body {max-width: 400px; margin:0px auto; padding-bottom: 25px;}

  </style>
</head>
<body>
  <h2>ESP32 SD Web Server</h2>
  <h3>Made by Anthony Sedore</h3>
  <p><span id="textSliderValue">%SLIDERVALUE%</span></p>
  <p><input type="range" onchange="updateSliderPWM(this)" id="pwmSlider" min="0" max="100" value="%SLIDERVALUE%" step="1" class="slider2"></p>
  %BUTTONPLACEHOLDER%
</body>
</html>
)rawliteral";

// Replaces placeholder with button section in your web page
String processor(const String& var) {
  //Serial.println(var);
  if (var == "SLIDERVALUE") {
    return sliderValue;
  }

  if (var == "BUTTONPLACEHOLDER") {
    String buttons = "";
    buttons += "<h4>Forward | Backward</h4><label class=\"switch\"><input type=\"checkbox\" onchange=\"toggleCheckbox(this)\" id=\"2\" " + outputState(2) + "><span class=\"slider3\"></span></label>";
    buttons += "<h4>OFF | ON</h4><label class=\"switch\"><input type=\"checkbox\" onchange=\"toggleCheckbox(this)\" id=\"4\" " + outputState(4) + "><span class=\"slider\"></span></label>";
    return buttons;
  }

  return String();
}



void setup()
{
  delay(50);
  Serial.begin(115200);
  SDsetup();

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) 
  {
    delay(500);
    Serial.print(".");
  }

    Serial.println("");
    Serial.println("WiFi connected.");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
    
    server.on("/", HTTP_GET, [](AsyncWebServerRequest* request) { request->send_P(200, "text/html", index_html, processor);});

    server.begin();



}

void loop(){
  WiFiClient client = server.available();   // listen for incoming clients
  
}