#include "ESP8266WiFi.h"
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>

// WiFi Parameters
const char* ssid = "Aura";
const char* password = "Akshay.20";

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting...");
  }
}

void loop() {
  // Check WiFi Status
  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("Connected");
   HTTPClient http;

// Send request
http.begin("http://coronavirus-19-api.herokuapp.com/countries");
http.GET();

// Print the response
Serial.print(http.getString());

// Disconnect
http.end();
      //Close connection
  }
  // Delay
  delay(30000);
}
