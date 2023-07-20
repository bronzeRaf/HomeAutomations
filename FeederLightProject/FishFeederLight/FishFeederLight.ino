// Motor A connections
int enA = 9;
int in1 = 8;
int in2 = 7;
int motor_speed = 100;              // For PWM maximum possible values are 0 to 255
float repeatInterval = 60000*60*8;  // ms*Min*Hrs
float enableInterval = 1000*3;   // ms*secs

void setup() {
  // Set the motor control pins to outputs
  pinMode(enA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  
  // Turn off motor - Initial state
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);

  // Set speed to the motor
  analogWrite(enA, motor_speed);
}

void loop() {
  enable_motor();
  delay(enableInterval);
  disable_motor();
  delay(repeatInterval);
}

// This function starts the motor
void enable_motor(){
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
}

// This function stops the motor
void disable_motor(){
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
}
