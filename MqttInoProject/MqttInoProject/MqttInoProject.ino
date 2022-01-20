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
  pinMode(led, OUTPUT);
  digitalWrite(led, HIGH);
  Cayenne.virtualWrite(V0, 0);
}

void loop() {
  // put your main code here, to run repeatedly:
  Cayenne.loop();
}

CAYENNE_IN(V0)
{
  int i = getValue.asInt();
  digitalWrite(2, !i);
}
