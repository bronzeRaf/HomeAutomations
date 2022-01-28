/*************************************************************
This is an IoT project using the Blynk Platform.

Hardware:
-NodeMCU board
-2 relays connected to Digital pins

Virtual pins:
V0: led

This project controls 2 relays through the internet to implement a home automation.
The duration of the ON relays is monitored and after 20min the ralays automatically turn OFF
The date and the duration of the last ON is stored as history.
The project is paired with an Android app.

18/01/2022 Raf Bronze rnm1816@gmail.com

 *************************************************************/

#include "secrets.h"
#include <CayenneMQTTESP8266.h>

// MQTT Broker credentials
char MQTT_USERNAME[] = SECRET_MQTT_USERNAME;
char MQTT_PASSWORD[] = SECRET_MQTT_PASSWORD;
char MQTT_CLIENT_ID[] = SECRET_MQTT_CLIENT_ID;
char MQTT_SERVER[] = SECRET_MQTT_SERVER;
char MQTT_PORT[] = SECRET_MQTT_PORT;

// WiFi credentials
char ssid[] = SECRET_SSID;
char pass[] = SECRET_PASS;

int led = 2;        //led pin
int relay1 = 12;    //D6 pin
int relay2 = 14;    //D5 pin
int heater = 0;     //on-off


void setup() {
  // Debug console
  Serial.begin(9600);
  Cayenne.begin(MQTT_USERNAME, MQTT_PASSWORD, MQTT_CLIENT_ID, ssid, pass);
  // Define pins
  pinMode(led, OUTPUT);
  pinMode(relay1, OUTPUT);
  pinMode(relay2, OUTPUT);
  // Initialize pins
  digitalWrite(led, HIGH);
  digitalWrite(relay1, LOW);
  digitalWrite(relay2, LOW);
  Cayenne.virtualWrite(V0, 0);
}

void loop() {
  Cayenne.loop();
}

CAYENNE_IN(V0){
  heater = getValue.asInt();
  Serial.println(heater);
  digitalWrite(led, !heater);
  digitalWrite(relay1, heater);
  digitalWrite(relay2, heater);
}

// Function to turn OFF the heater
void turnOFFheater(){
  // Turn Off relays
  digitalWrite(relay1,LOW);
  digitalWrite(relay2,LOW);
  heater = 0;
  // Turn OFF button
  Cayenne.virtualWrite(V0, 0);
}

// Function to turn OFF the heater
void turnONheater(){
  // Turn On relays
  digitalWrite(relay1,HIGH);
  digitalWrite(relay2,HIGH);
  heater = 1;
  // Get stop time
  // Turn ON button
  Cayenne.virtualWrite(V0, 1);
}
