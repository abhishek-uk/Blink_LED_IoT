#include <ESP8266WiFi.h>
#include "ThingSpeak.h"

#ifndef STASSID
#define STASSID "OnePlus 9RT 5G"
#define STAPSK "34567890"
#endif

#define DEBUG   // Uncomment to enable debugging

const char* SSID = STASSID;
const char* PASSWORD = STAPSK;

bool ledState = false;

void connectWifi();

unsigned long channel_Number = 2391019;
const char* readAPIKey = "LUCKBEOLHMVODMAE";

int statusCode = 0;

WiFiClient client;  // Create a WiFi client object to communicate with ThingSpeak

void setup() {
  Serial.begin(9600);

  WiFi.mode(WIFI_STA);
  WiFi.begin(SSID, PASSWORD);
  connectWifi();
  #ifdef DEBUG
    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());
  #endif

  pinMode(D0, OUTPUT);

  ThingSpeak.begin(client);  // Initialize ThingSpeak with the WiFi client
}

void loop() {
  if(WiFi.status() != WL_CONNECTED) {  // check the wifi and reconnect if disconnected
    #ifdef DEBUG
      Serial.println("WiFi Disconnected");
    #endif
    connectWifi();
  }

  if(ledState == 1) {
    digitalWrite(D0, HIGH);
  } else if (ledState == 0) {
    digitalWrite(D0, LOW);
  }

  statusCode = ThingSpeak.readMultipleFields(channel_Number, readAPIKey);
  if (statusCode == 200) {
    ledState = ThingSpeak.getFieldAsInt(1);
  }

  // Serial.println(statusCode);
  // Serial.println(ledState);
}

void connectWifi() {
  while(WiFi.status() != WL_CONNECTED) {
    #ifdef DEBUG 
      Serial.print(". ");
    #endif
    delay(400);
  }
  #ifdef DEBUG
    Serial.println("WiFi connected ");
  #endif
}
