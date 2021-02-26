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

// Handle reception of incoming I2C data  
/*
 * Data que se espera:
 * 1 - Forward
 * 2 - Backward
 * 3 - Right
 * 4 - Left
 * 5 - Stop
 * Futuro cambio: 
 *     Mandar comando Forward/Backward y velocidad separados por coma.
 *     Mandar comando left/Right con grados en giro del servo
 * 
 */
void receiveData(int byteCount) {  
  analizaDistancia();
  while (Wire.available()) {  
    i2cData = Wire.read(); 
    Serial.println(i2cData);
    switch(i2cData){
       case 1:
            Serial.println("Forward");
            MotorSpeed1 = 250;
            analogWrite(pwmA, MotorSpeed1);
            digitalWrite(STBY, HIGH); // iniciamos activando
            digitalWrite(in1A, LOW);
            digitalWrite(in2A, HIGH);
            // digitalWrite(13,HIGH);
            break;
       case 2:
            Serial.println("Back");
            MotorSpeed1 = 250;
            analogWrite(pwmA, MotorSpeed1);
            digitalWrite(STBY, HIGH); // iniciamos activando
            digitalWrite(in1A, HIGH);
            digitalWrite(in2A, LOW);
            
            // digitalWrite(13,LOW);
            break;
       case 3:
            delay(5000);
            servo1.write(45);
            // digitalWrite(13,HIGH);
            break;
       case 4:

            delay(5000);
            servo1.write(135);
            // digitalWrite(13,LOW);
            break;
       case 5:
            delay(5000);
            servo1.write(90);
            break;
       case 6:
            digitalWrite(STBY, LOW); // iniciamos activando
            break;
     } 
  }  
}  
// Handle request to send I2C data  
void sendData() {   
  Wire.write(i2cData);  
}

void analizaDistancia()
{
 // Clears the trigPin condition
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distance = duration * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
  // Displays the distance on the Serial Monitor
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");
  
  if (distance <= 5) // hay obstaculo
  {
      obstaculo = true;
      i2cData = 1;
  }
  else  // avanzamos
  {
      obstaculo = false;
      i2cData = 0;
  }
  
  
}
 
void loop()
{

 
}

 
