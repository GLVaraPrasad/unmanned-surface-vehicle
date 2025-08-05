/*
  surface_vehicle.ino
  -------------------
  Arduino code for RF-controlled aquatic surface vehicle.
  Controls: 
    - 2 DC motors (propulsion)
    - 1 DC motor (conveyor)
    - 1 servo motor (weed cutter)
  Author: G. Lakshmi Vara Prasad
  Project: JRF - TIH-TIDF, IIT Guwahati
*/

#include <IBusBM.h> // Including iBusBM Library
#include <Servo.h>

// Create iBus object
IBusBM ibus; 
Servo myservo;
int pos = 0;
int val;

// Motor A pin connections
const int dir1 = 12;
const int pwm1 = 11;
// Motor B pin connections
const int dir2 = 7;
const int pwm2 = 6;

// Roller Motor Pin connections
const int InA  = 5;
const int InB  = 4;
const int pwm3 = 3;

// Read the number of a given channel and convert to the range provided.
// If the channel is off, return the default value
int readChannel(byte channelInput, int minLimit, int maxLimit, int defaultValue){
  uint16_t ch = ibus.readChannel(channelInput);
  if(ch < 100) return defaultValue;
  return map(ch,1000,2000,minLimit,maxLimit);
}

// Read the channel and return a boolean value
bool readSwitch(byte channelInput, bool defaultValue){
  int intDefaultValue = (defaultValue) ? 100 : 0;
  int ch = readChannel(channelInput, 0, 100, intDefaultValue);
  return (ch > 50);
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

  // Setting motor pins
  pinMode(dir1, OUTPUT);
  pinMode(pwm1, OUTPUT);
  pinMode(dir2,OUTPUT);
  pinMode(pwm2,OUTPUT);
  pinMode(InA,OUTPUT);
  pinMode(InB,OUTPUT);
  pinMode(pwm3,OUTPUT);
  myservo.attach(9);
  myservo.write(pos);

  // Attach iBus object to serial port
  ibus.begin(Serial);

  // Initially setting motor in off position
  digitalWrite(dir1,LOW);
  digitalWrite(dir2,LOW);
  digitalWrite(InA,LOW);
  digitalWrite(InB,LOW);
  analogWrite(pwm1,0);
  analogWrite(pwm2,0);
  analogWrite(pwm3,0);
  delay(100);

}

void loop() {
  // Cycle through first 5 channels and determine values
  // Print values to serial monitor
  // Note IBusBM library labels channels starting with "0"

  for (byte i = 0; i < 5; i++){
    // This channel is used for the motor speed 0 to 255
    if (i == 1) {
      int value = readChannel(i, -255, 255, 0);
      Serial.print("Ch");
      Serial.print(i + 1);
      Serial.print(": ");
      Serial.print(value);
      Serial.print(" | ");
    }
    else if(i == 4){
      int value = readChannel(i, 0, 255, 0);
      Serial.print("Ch");
      Serial.print(i + 1);
      Serial.print(": ");
      Serial.print(value);
      Serial.print(" | ");
    }
    else {
      int value = readChannel(i, -100, 100, 0);
      Serial.print("Ch");
      Serial.print(i + 1);
      Serial.print(": ");
      Serial.print(value);
      Serial.print(" | ");  
    }
  }
 
  // Print channel 6 (switch) boolean value
  Serial.print("Ch6: ");
  Serial.print(readSwitch(5, false));
  Serial.println(); 

  int ch1_val = readChannel(0,-100,100,0);
  int ch2_val = readChannel(1,-255,255,0);
  int ch3_val = readChannel(2,-100,100,0);
  int ch4_val = readChannel(3,-100,100,0);
  int ch5_val = readChannel(4,0,255,0);
  int ch6_val = readSwitch(5,false);

  int armed_x = ch3_val;
  int armed_y = ch4_val;
  int direction = ch2_val;
  int turn = ch1_val;
  int access = ch6_val;
  int conv_speed = ch5_val;
  motor_control(armed_x,armed_y,direction,turn,access); //function to control the motor directions
  conveyor_control(conv_speed,pos); // function to control the speed of the conveyor belt
  //servo_control(pos); // function to control the servo

}

void motor_control(int arm_x,int arm_y, int speed,int turn,int access){
  if(arm_x <= -95 && arm_y == -100){
    if (access == 0){
      // forward direction
      if (speed > 0 ){
      digitalWrite(dir1,LOW);
      digitalWrite(dir2,LOW);
      analogWrite(pwm1,abs(speed));
      analogWrite(pwm2,abs(speed));
      delay(10);
      }
      //Backward direction
      else {
        digitalWrite(dir1,HIGH);
        digitalWrite(dir2,HIGH);
        analogWrite(pwm1,abs(speed));
        analogWrite(pwm2,abs(speed));
        delay(10);
      }
    }
    else{
      if(turn < -90){
      digitalWrite(dir1,LOW);
      digitalWrite(dir2,LOW);
      analogWrite(pwm1,80);
      analogWrite(pwm2,160);
      delay(10);

    }
    //Right direction
      else if(turn > 90){
      digitalWrite(dir1,LOW);
      digitalWrite(dir2,LOW);
      analogWrite(pwm1,160);
      analogWrite(pwm2,80);
      delay(10);
    }
    else{
      digitalWrite(dir1,LOW);
      digitalWrite(dir2,LOW);
      analogWrite(pwm1,0);
      analogWrite(pwm2,0);
      delay(10);
    }

    }

  }
  
}

void conveyor_control(int conv_speed,int pos){
  if (conv_speed == 0){
    digitalWrite(InA,LOW);
    digitalWrite(InB,LOW);
    analogWrite(pwm3,0);
    delay(10);
  } 
  else if(conv_speed == 255){
    digitalWrite(InA,HIGH);
    digitalWrite(InB,LOW);
    analogWrite(pwm3,255);
    delay(10);
  }
  else{
    servo_control(pos); // function to control the servo 
  }
  delay(100);

}

void servo_control(int pos){
  for (pos = 0; pos <=80 ; pos = pos + 10) { 
    myservo.write(pos);              
    delay(10);                       
  }
  for (pos = 80; pos >= 0; pos = pos - 10) { 
    myservo.write(pos);              
    delay(10);                       
  }
}
