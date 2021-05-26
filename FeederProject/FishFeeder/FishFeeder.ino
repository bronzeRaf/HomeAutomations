/* FishFeeder
  Author: Bronze Raf
  This code implements an automatic fish feeder.

  Uncomment Debug Serial prints, in order to monitor the process
  May 2021
*/

#include "Button.h"
#include <Servo.h>

//-------------------------ABSTRACT LEVEL-------------------------
namespace Hardware {
//typedef class Task Task;
extern "C" {
  class Task;
  typedef void (*callbackTaskEvent)(Task * task);
  typedef unsigned long ulong;
}

class Task {
  private:
      enum TaskState {
        ENABLED,
        DISABLED
      };

    ulong _sleepTill = 0;
    ulong _sleepStashTill = 0;
    virtual void runloop() = 0;
    TaskState _stateTask = DISABLED;
       
  public:
    callbackTaskEvent loopCallback = NULL;
    
    void sleep(ulong timedelay) {
      _sleepTill = millis() + timedelay;
    }

    void run() {
      if (_stateTask == DISABLED || _sleepTill > millis()) {
        return;
      }
      if (loopCallback != NULL) {
        loopCallback(this);
      } else {
        runloop();
      }
    }

    ulong getSleepTime(){
      return _sleepTill;
    }

    void stashSleepTime(){
      _sleepStashTill = _sleepTill;
    }

    void stashApplyTime(){
      _sleepTill = _sleepStashTill;
      _sleepStashTill = 0;
    }

    void setEnabled(){
      _stateTask = ENABLED;
    }

    void setDisabled(){
      _stateTask = DISABLED;
    }

};
};
//----------------------------------------------------------------

//--------------------------DEFINE TASKS--------------------------
using Hardware::Task;
//
class LedTask: public Hardware::Task {
    int pin = LED_BUILTIN;
    int state = 0;
    int repeatCount = 4;
    int repeatIndex = 0;

    public: void setup(){
      pinMode(pin, OUTPUT);
    }

    void runloop() override {
      state = state ^ 1;
      digitalWrite(LED_BUILTIN, state==0?LOW:HIGH);   // turn the LED on (HIGH is the voltage level)
      //Serial.println(state,DEC); 
      if ( repeatIndex >= repeatCount ) {
        state = 0;
        repeatIndex = 0;
        sleep(30000); 
        digitalWrite(LED_BUILTIN, LOW);
        //Serial.println("LedTask : runloop sleep"); 
        return;
      }
      
      repeatIndex = repeatIndex + 1;
      sleep(500); 
    }
};

class ServoTask: public Hardware::Task {
    Servo servo;
    const int pin = 9;
    int maxAngle = 179; //some Servos could stack at 180, so reduce this value to 169 for example.
    int currentAngle = 0;
    int stepSize = 1;
    int repeatIndex = 0;
    
    int force = 0;
    unsigned long forceTimeRestore = 0;
    
    public: 
      int speed = 3;                      //how fast servo moves
      int repeatCount = 1;                //how many moves to laft-right
      unsigned long repeatInterval = 0;   // delay to next move series
    
    public: void setup() {
        servo.attach(9);
        servo.write(0);
    }

    public: void forceRun(){
      force = 1;
      stashSleepTime();
      sleep(0);
    }

    void runloop() override {
      //Serial.println("ServoTask : runloop"); 
      currentAngle = currentAngle + stepSize;
      if (currentAngle <= 0 || currentAngle >= maxAngle) {
        stepSize = -stepSize;
      }
      servo.write(currentAngle);
      sleep(speed);

      if ( repeatIndex >= repeatCount ) {
        repeatIndex = 0;
        if (force == 1) {
//          restore scheduler
          stashApplyTime();
          //Serial.println("forceTimeRestore"); 
        }
        else {
          sleep(repeatInterval); 
          //Serial.println("repeatInterval sleep"); 
        }
        force = 0;
        return;
      }
      
      if (currentAngle == 0) {
        repeatIndex = repeatIndex + 1;
      }
    }
};

class SensorTask: public Hardware::Task {
    int pin = A0;
    public: int valueServoRepeatCount = 5;    
    public: unsigned long valueServoFrequency = 3;
    public: Hardware::callbackTaskEvent onValueChanged = NULL;
    
    void runloop() override {
      int r = map(analogRead(pin),0,1024,1,30) ;
      if (valueServoRepeatCount != r) {
        valueServoRepeatCount = r;
        if (onValueChanged !=NULL) {
          onValueChanged(this);
        }
      }  
      sleep(10);
    }
}; 
//----------------------------------------------------------------


/* Global Variables*/
ServoTask servo;
SensorTask sensor;
LedTask led;
Hardware::Button button = Hardware::Button(8);
unsigned long timer = 0;

//--------------------------EVENT METHODS-------------------------
void onSensorValueChanged(){
  //Serial.print("valueServoRepeatCount=");  
  //Serial.println(task->valueServoRepeatCount,DEC);  
  servo.repeatCount = sensor.valueServoRepeatCount;
  
  //Serial.print("valueServoFrequency=");  
  //Serial.println(task->valueServoFrequency,DEC);  
  servo.speed = sensor.valueServoFrequency;
}

void onPress(Hardware::Button& sender){
  //Serial.println("onPress");
  servo.forceRun();
}
//----------------------------------------------------------------

void setup() {
  // Debug
  //Serial.begin(9600);
  // Servo setup
  servo.setup();
  servo.repeatInterval = 60000*60*8; // ms*Min*Hrs
  servo.setEnabled();
  // Led setup
  led.setup();
  led.setEnabled();  
  // Potentiometer setup
  sensor.setEnabled();
  sensor.onValueChanged = &onSensorValueChanged;
  // Button setup
  button.onPress = &onPress;
}

void loop() {
  sensor.run();  
  servo.run();
  led.run();
  button.update();
}
