#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoOTA.h>
#include <ArduinoJson.h>
#include <arduino-timer.h>
#include "secrets.h"

#define NUM_BUTTONS 3
#define DEVICE_NAME "COMMAND_CONTROL"

auto timer = timer_create_default();
bool accessoryState[NUM_BUTTONS] = {
  true,
  true,
  true
};

String accessoryIds[NUM_BUTTONS] = {
  "e4758a7f3...", // Accessory 1
  "418aa0aea...", // Accessory 2
  "814a3beda..."  // Accessory 3
};

int buttonPin[NUM_BUTTONS] = { D5, D6, D7 };
int ledPin[NUM_BUTTONS] = { D1, D2, D3 };


HTTPClient http;
WiFiClient client;


void setup() {
  pinMode(D1, OUTPUT);
  pinMode(D2, OUTPUT);
  pinMode(D3, OUTPUT);

  pinMode(D5, INPUT);
  pinMode(D6, INPUT);
  pinMode(D7, INPUT);

  Serial.begin(115200);
  
  Serial.print("Device name: ");
  Serial.println(DEVICE_NAME);

  Serial.print("Connecting to Wifi");
  Serial.println(WIFI_SSID);

  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(WiFi.SSID());
  Serial.print("IP address:\t");
  Serial.println(WiFi.localIP());

  setupArduinoOTA();

  timer.in(100, refreshAuth);            // Initial Authentication
  timer.in(1500, refreshAccessories);    // Get initial state of all buttons
  timer.every(28800000, refreshAuth);    // Refresh Auth in certain intervals
  timer.every(5000, refreshAccessories); // Refresh the state of all buttons periodically
}

void loop() {
  ArduinoOTA.handle();
  timer.tick();

  for (int i = 0; i < NUM_BUTTONS; i++) {
    digitalWrite(ledPin[i], accessoryState[i] ? HIGH : LOW);
  }

  for (int i = 0; i < NUM_BUTTONS; i++) {
    if (digitalRead(buttonPin[i]) == HIGH) {
       toggleAccessory(accessoryIds[i], !accessoryState[i]);
       accessoryState[i] = !accessoryState[i];
       digitalWrite(ledPin[i], accessoryState[i] ? HIGH : LOW);
       delay(500);
    }
  }
}
