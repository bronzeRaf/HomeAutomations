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
BlynkTimer timer;

// WiFi credentials.
char ssid[] = SECRET_SSID;
char pass[] = SECRET_PASS;
// Other Global variables
int relay1 = 12;   //D6 pin
int relay2 = 14;  //D5 pin
int heater = 0;   //on-off
int heaterPin = 10;    //heater state pin
int heaterState;        //heater state value
// Time variables
unsigned long lastsession = 0;
unsigned long starttime = 0;
unsigned long stoptime = 0;
int nowminutes = 0;
int nowseconds = 0;
int lastminutes = 0;
int lastseconds = 0;
String datestamp;
String timestamp;

boolean fromReboot;
int button;

// Function called everytime the device connects to the server
BLYNK_CONNECTED() {
    Serial.println(fromReboot);
    Serial.println(button);
    Blynk.syncVirtual(V10);
    Serial.println("V10");
    Serial.println(heaterState);
    heater = 0;
    // Connected after disconnect
    if (!fromReboot){
      sendLastSession();          //send session time
    }
    else{
      if(heaterState==1){
        Blynk.virtualWrite(V0, 0);  //turn off button
        sendLastSession();          //send session time
      }
    }
}


// Function called every second to check connectivity
void myTimerEvent(){
  //check if device connected to server
  if (Blynk.connected()){
    Serial.println("Connected");
    if (heater==1){
      //send live time
      sendLiveSession();
      //turn off after 20min automatically
      if (nowminutes > 19){
        digitalWrite(relay1,LOW);   //turn off relay1
        digitalWrite(relay2,LOW);   //turn off relay2
        Blynk.virtualWrite(V0, 0);  //turn off button
        heater=0;
        sendLastSession();          //send session time
      }
    }
  }
  else{
    Serial.println("Disconnected");
    digitalWrite(relay1,LOW);   //turn off relay1
    digitalWrite(relay2,LOW);   //turn off relay2


    //*******************
    // Disconnect Detected SOS TODO resolving
    if (heater ==1){
      //store time

      heater = 0;
      fromReboot = false;
    }
    else{
      
    }
    //********************

    
    
    // connect to the server
    startConnection();
  }
}


// Function called when button is triggered
BLYNK_WRITE(V0){
  button = param.asInt();         //get value as integer
  Blynk.virtualWrite(V10, button); //store heater state

  if (button == 0){
    //turn off
    Serial.println(button);
    digitalWrite(relay1,LOW);
    digitalWrite(relay2,LOW);
    heater = 0;
    stoptime = millis();        //get stop time
    sendLastSession();          //send session time
  }
  else{
    //turn on
    Serial.println(button);
    digitalWrite(relay1,HIGH);
    digitalWrite(relay2,HIGH);
    heater = 1;
    starttime = millis();       //get start time
    //request timestamp
    Blynk.sendInternal("rtc", "sync");
  }
}

// Function called when button is triggered
BLYNK_WRITE(V10){
  heaterState = param.asInt();   //get value as integer
}

//Function called everytime the server sends timestamp
BLYNK_WRITE(InternalPinRTC) {
  long t = param.asLong();
  //convert time
  struct tm* now = localtime(&t);
  //create strings
  datestamp = String(now->tm_mday)+"/"+String(now->tm_mon+1)+"/"+String(now->tm_year+1900);
  timestamp = String(now->tm_hour)+":"+String(now->tm_min);
  Serial.println(datestamp+" "+timestamp);
}

// Function called to store last session time and to initialize live time
void sendLastSession(){
  lastminutes = nowminutes;
  lastseconds = nowseconds;
  Blynk.virtualWrite(V6, lastminutes);  //send lastsession minutes
  Blynk.virtualWrite(V7, lastseconds);  //send lastsession seconds
  Blynk.virtualWrite(V2, 0);            //erase live minutes
  Blynk.virtualWrite(V3, 0);            //erase live seconds
  //send datetime to the server
  Blynk.virtualWrite(V8, datestamp+" "+timestamp);
}

// Function called to store live session time
void sendLiveSession(){
  unsigned long now = millis();
  //check for millis overflow
  if (now < starttime){
    //initialize again
    starttime = millis();
    now = millis();
    //store last session
    sendLastSession();
  }
  //calculate on time
  nowminutes = ((now - starttime)/1000)/60;
  nowseconds = (now - starttime)/1000 - nowminutes*60;
  Blynk.virtualWrite(V2, nowminutes);  //send live seconds
  Blynk.virtualWrite(V3, nowseconds);  //send live seconds
}

// Function that sets up the connection to the server
void startConnection(){
  //configure connection
  Blynk.begin(auth, ssid, pass);
  //configure callback
  timer.setInterval(1000L, myTimerEvent);
}

void setup(){
  fromReboot = true;
  // Debug console
  Serial.begin(9600);
  //pins setup
  pinMode(relay1, OUTPUT);
  pinMode(relay2, OUTPUT);
  // connect to the server
  startConnection();
}


void loop(){
  Blynk.run();  //fire up blynk
  timer.run();  //fire up the callback
}
