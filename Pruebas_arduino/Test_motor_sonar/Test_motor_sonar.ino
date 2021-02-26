#include <Wire.h>
#include <Servo.h>


#define i2cAddress 0x10
int i2cData = 0;

// Definicion de motor
Servo servo1;

// Motor A
int pwmA = 5;
int in1A = 3;
int in2A = 4;
int STBY = 9;

// Servo
int servoPin = 12;

// Motor Speed Values - Start at zero

int MotorSpeed1 = 0;
int MotorSpeed2 = 0;
int angle = 90;

// Sensor ultrasonic
#define echoPin 11 // attach pin D2 Arduino to pin Echo of HC-SR04
#define trigPin 10 //attach pin D3 Arduino to pin Trig of HC-SR04
// defines variables
long duration; // variable for the duration of sound wave travel
int distance; // variable for the distance measurement

bool obstaculo= false;
bool TakePicture = 0;

// Handle request to send I2C data  
void sendData() {   
  Wire.write(i2cData);  
}

void receiveData(int byteCount) {  

  
}

 
void setup()
{  
   Serial.begin(9600);
   Wire.begin(i2cAddress);  
   Wire.onReceive(receiveData);  // cuando llegue la data... se ejecuta esta funcion.
   Wire.onRequest(sendData);     // cuando queremos enviar
// LED
   pinMode(13,OUTPUT);
   digitalWrite(13,LOW);
// Definicion de Motor
  pinMode(pwmA, OUTPUT);

  pinMode(in1A, OUTPUT);
  pinMode(in2A, OUTPUT);

  pinMode(STBY, OUTPUT);

  digitalWrite(STBY, HIGH); // iniciamos activando
  
  servo1.attach(servoPin);
  servo1.write(90);
  delay(10000);
  servo1.write(45);
  delay(10000);
  servo1.write(135);
  delay(10000);
  // Sensor ultrasonic
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an OUTPUT
  pinMode(echoPin, INPUT); // Sets the echoPin as an INPUT
  obstaculo = false;
}


void loop() {

// Get distance
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);   
  digitalWrite(trigPin, HIGH);     // send waves for 10 us
  delayMicroseconds(10);
  duration = pulseIn(echoPin, HIGH); // receive reflected waves
  distance = duration / 58.2;   // convert to distance
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");
  delay(10);

  if (distance > 6)
  {   
      servo1.write(90);  // forward
      i2cData = 1;
      Serial.println("Forward");
      MotorSpeed1 = 250;
      analogWrite(pwmA, MotorSpeed1);
      digitalWrite(STBY, HIGH); // Activate motor
      Wire.onRequest(sendData); // Request picture to JEtson
      digitalWrite(in1A, LOW);
      digitalWrite(in2A, HIGH);
      i2cData = 0;
  }
  
  if (distance < 5)
  {
     digitalWrite(STBY, LOW); // stop motor
     analogWrite(pwmA, MotorSpeed1);
     digitalWrite(STBY, HIGH); // iniciamos activando
     digitalWrite(in1A, HIGH);  // Move backward
     digitalWrite(in2A, LOW);
     delay(500);
     digitalWrite(in1A, LOW);  // Move Forward
     digitalWrite(in2A, HIGH);     
     servo1.write(45);  // Turn Right
     
  }


}
