/*************************************************************
This is an IoT project using the Blynk Platform.

Hardware:
-NodeMCU board
-2 relays connected to Digital pins

This project controls 2 relays through the internet to implement a home automation.
The duration of the ON relays is monitored and after 20min the ralays automatically turn OFF
The date and the duration of the last ON is stored as history.
The project is paired with an Android app.

29/9/2020 Raf Bronze rnm1816@gmail.com

 *************************************************************/

#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <Time.h>
#include "secrets.h" // Sensitive data (ssid + password)

// Token to authenticate Android app
char auth[] = SECRET_TOKEN;
// Blynk timer for callback
BlynkTimer timer;

// WiFi credentials.
char ssid[] = SECRET_SSID;
char pass[] = SECRET_PASS;

// Other Global variables
int relay1 = 12;        //D6 pin
int relay2 = 14;        //D5 pin
int heater = 0;         //on-off
int heaterState=0;      //heater state value
boolean fromReboot;     //reboot or disconnected?
int button;             //button value
// Time variables
unsigned long lastsession = 0;
unsigned long starttime = 0;
int nowminutes = 0;
int nowseconds = 0;
int lastminutes = 0;
int lastseconds = 0;
String datestamp;
String timestamp;

// Function called everytime the device connects to the server
BLYNK_CONNECTED() {
    // Turn OFF heater
    turnOFFheater();
    // Connected after disconnect
    if (!fromReboot){
      sendLastSession();  //send session time
    }
}

// Function called every second to check connectivity
void myTimerEvent(){
  // Check if device connected to server
  if (Blynk.connected()){
    //Serial.println("Connected");
    if (heater==1){
      // Send live time
      sendLiveSession();
      // Turn off after 20min automatically
      if (nowminutes > 19){
        turnOFFheater();      //turn off heater
        sendLastSession();    //send session time
      }
    }
  }
  else{
    // Disconnect detected
    Serial.println("Disconnected");
    // Check if heater was ON
    if (heater ==1){
      // Store time on next connection
      fromReboot = false;
    }
    // Turn OFF heater
    turnOFFheater();
    // Connect to the server
    startConnection();
  }
}

// Function called when button is triggered
BLYNK_WRITE(V0){
  // Obtain button value
  button = param.asInt();           //get value as integer
  if (button == 0){
    // Turn off
    Serial.println(button);
    // Turn off heater
    turnOFFheater();
    sendLastSession();          //send session time
  }
  else{
    // Turn on
    Serial.println(button);
    digitalWrite(relay1,HIGH);
    digitalWrite(relay2,HIGH);
    heater = 1;
    starttime = millis();       //get start time
    //request timestamp
    Blynk.sendInternal("rtc", "sync");
  }
}

// Function called everytime the server sends timestamp
BLYNK_WRITE(InternalPinRTC) {
  long t = param.asLong();
  // Convert time
  struct tm* now = localtime(&t);
  // Create time strings
  datestamp = String(now->tm_mday)+"/"+String(now->tm_mon+1)+"/"+String(now->tm_year+1900);
  timestamp = String(now->tm_hour)+":"+String(now->tm_min);
  Serial.println(datestamp+" "+timestamp);
}

// Function to turn OFF the heater
void turnOFFheater(){
  // Turn Off relays
  digitalWrite(relay1,LOW);
  digitalWrite(relay2,LOW);
  heater = 0;
  // Get stop time
  // Turn OFF button
  Blynk.virtualWrite(V0, 0);
  // Erase live time
  Blynk.virtualWrite(V2, 0);            //erase live minutes
  Blynk.virtualWrite(V3, 0);            //erase live seconds
}

// Function called to store last session time and to initialize live time
void sendLastSession(){
  // Take last live time
  lastminutes = nowminutes;
  lastseconds = nowseconds;
  Blynk.virtualWrite(V6, lastminutes);  //send lastsession minutes
  Blynk.virtualWrite(V7, lastseconds);  //send lastsession seconds
  // Send datetime to the server
  Blynk.virtualWrite(V8, datestamp+" "+timestamp);
}

// Function called to store live session time
void sendLiveSession(){
  unsigned long now = millis();
  // Check for millis overflow
  if (now < starttime){
    // Initialize again
    starttime = millis();
    now = millis();
    // Store last session
    sendLastSession();
  }
  // Calculate ON time
  nowminutes = ((now - starttime)/1000)/60;
  nowseconds = (now - starttime)/1000 - nowminutes*60;
  Blynk.virtualWrite(V2, nowminutes);  //send live seconds
  Blynk.virtualWrite(V3, nowseconds);  //send live seconds
}

// Function that sets up the connection to the server
void startConnection(){
  // Configure connection
  Blynk.begin(auth, ssid, pass);
  // Configure timer callback
  timer.setInterval(1000L, myTimerEvent);
}

void setup(){
  // Initialize reboot
  fromReboot = true;
  // Debug console
  Serial.begin(9600);
  // Pins setup
  pinMode(relay1, OUTPUT);
  pinMode(relay2, OUTPUT);
  // Connect to the server
  startConnection();
}


void loop(){
  Blynk.run();  //fire up blynk
  timer.run();  //fire up the timer callback
}
