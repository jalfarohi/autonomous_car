/*
  TB6612FNG H-Bridge Demo
  TB6612-Demo.ino
  Demonstrates use of TB6612FNG H-Bridge Motor Controller
  Drives two DC Motors
 
  DroneBot Workshop 2019
  https://dronebotworkshop.com
*/
#include <Servo.h>

Servo servo1;
// Motor A
 
int pwmA = 5;
int in1A = 3;
int in2A = 4;

int servoPin = 12;

int STBY = 9;
// Speed control potentiometers
 
int SpeedControl1 = A0;  

  
// Motor Speed Values - Start at zero
 
int MotorSpeed1 = 0;
int MotorSpeed2 = 0;
int angle = 0;
void setup()
 
{
 
  // Set all the motor control pins to outputs
 
  pinMode(pwmA, OUTPUT);

  pinMode(in1A, OUTPUT);
  pinMode(in2A, OUTPUT);

  pinMode(STBY, OUTPUT);

  digitalWrite(STBY, HIGH); // iniciamos activando
   servo1.attach(servoPin);
}
 
void loop() {
  
  // Set Motor A forward
 
  digitalWrite(in1A, HIGH);
  digitalWrite(in2A, LOW);

  // Set the motor speeds
  MotorSpeed1 = 250;
     analogWrite(pwmA, MotorSpeed1);

    // delay(9000);
    
    servo1.write(90);
    delay(5000);
    
  // Sweep from 0 to 180 degrees:
  //for (angle = 45; angle <= 135; angle += 1) {
  for (angle = 90; angle <= 135; angle += 1) {
    servo1.write(angle);
    delay(15);
  }
  
  // And back from 180 to 0 degrees:
  // for (angle = 135; angle >= 45; angle -= 1) {
  for (angle = 90; angle >= 45; angle -= 1) {
    servo1.write(angle);
    delay(15);
    
  }
  

}
