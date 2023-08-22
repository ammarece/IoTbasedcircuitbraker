/*
Code Name:Internet of things based circuit breaker
Author: @ammarece
Description: This program is Internet of things based circuit breaker
License: Remixing or Changing this Thing is allowed. Commercial use is not allowed.
*/
#define BLYNK_TEMPLATE_ID "TMPL3-CX-hXzc"
#define BLYNK_TEMPLATE_NAME "CKT breaker"
#define BLYNK_AUTH_TOKEN "OjaN9MH3UfRPgj68HeNqfjTbAL55ygS3"
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

// WiFi credentials
char ssid[] = "iMaK";
char pass[] = "gate@024";

// Blynk authentication token
char auth[] = "OjaN9MH3UfRPgj68HeNqfjTbAL55ygS3";

// Virtual pins for controlling the relays
#define RELAY_PIN_1 V0
#define RELAY_PIN_2 V1
#define RELAY_PIN_3 V2
#define RELAY_PIN_4 V3

// Relay state
bool relayState[4] = {LOW, LOW, LOW, LOW};

void setup() {
  // Initialize serial communication
  Serial.begin(115200);

  // Connect to WiFi
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");

  // Initialize Blynk
  Blynk.begin(auth, WiFi.SSID().c_str(), WiFi.psk().c_str());

  // Set up relay pins as output
  pinMode(D0, OUTPUT); // GPIO16 on NodeMCU board
  pinMode(D1, OUTPUT); // GPIO5 on NodeMCU board
  pinMode(D2, OUTPUT); // GPIO4 on NodeMCU board
  pinMode(D3, OUTPUT); // GPIO0 on NodeMCU board

  // Attach relay control function to Blynk virtual pins
  Blynk.virtualWrite(RELAY_PIN_1, relayState[0]);
  Blynk.virtualWrite(RELAY_PIN_2, relayState[1]);
  Blynk.virtualWrite(RELAY_PIN_3, relayState[2]);
  Blynk.virtualWrite(RELAY_PIN_4, relayState[3]);
}

void loop() {
  Blynk.run();
}

// Function to control relays based on Blynk commands
BLYNK_WRITE(RELAY_PIN_1) {
  int pinValue = param.asInt();
  digitalWrite(D0, pinValue);
  relayState[0] = pinValue;
}

BLYNK_WRITE(RELAY_PIN_2) {
  int pinValue = param.asInt();
  digitalWrite(D1, pinValue);
  relayState[1] = pinValue;
}

BLYNK_WRITE(RELAY_PIN_3) {
  int pinValue = param.asInt();
  digitalWrite(D2, pinValue);
  relayState[2] = pinValue;
}

BLYNK_WRITE(RELAY_PIN_4) {
  int pinValue = param.asInt();
  digitalWrite(D3, pinValue);
  relayState[3] = pinValue;
}
