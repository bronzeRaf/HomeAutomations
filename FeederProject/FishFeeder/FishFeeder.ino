/* FishFeeder
  by Bronze Raf
  This code implements an automatic fish feeder.

  modified 12 August 2020
  by Bronze Raf
*/

#include <Servo.h>

Servo myservo;    // create servo object to control a servo
const unsigned long SECOND = 1000;      // second in millis
const unsigned long HOUR = 3600*SECOND; // hour in millis

//servo 140 degrees is wide open and 35 is totally closed
int openFeeder = 80;    // servo degrees for open feeder
int closedFeeder = 35;   // servo degrees for closed feeder
int timeOn = 2*SECOND;  // time servo stays in open position

void setup() {
  myservo.attach(2);  // attaches the servo on D4 to the servo object
}

void loop() {
  // close feeder
/*   myservo.write(closedFeeder);
  delay(12*HOUR);
  // open feeder
  myservo.write(openFeeder);
  delay(timeOn);
*/

      // test positions
      myservo.write(closedFeeder);
      delay(1000);
      myservo.write(openFeeder);
      delay(100);
      myservo.write(closedFeeder);
      delay(12*HOUR);
      
}
