#include <MPU6050_tockn.h>

/* HC-SR04 ultrasonic distance sensor with NewPing library example code. More info: www.makerguides.com */
// Include the library:
#include <NewPing.h>
// Define pins and max distance:
#define trigPin  6
#define echoPin  5
#define trigPin2 8
#define echoPin2 7
#define MAX_DISTANCE 350 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.
#include <MPU6050_tockn.h>
#include <Wire.h>

MPU6050 mpu6050(Wire);
NewPing sonar(trigPin, echoPin, MAX_DISTANCE); // NewPing setup of pins and maximum distance.
NewPing sonar2(trigPin2, echoPin2, MAX_DISTANCE);
float duration, distance;
float duration2, distance2;
int ledPin =13;
int ledPin2 =12;
const int buzzer = 9;
const int buzzer2 = 10;
long timer = 0;
void setup() {
  Serial.begin(9600); // Open serial monitor at 9600 baud to see ping results.
  pinMode(ledPin,OUTPUT);
  pinMode(ledPin2,OUTPUT);
  pinMode(buzzer,OUTPUT);
  pinMode(buzzer2,OUTPUT);

  /*----------MPU6050 code------------*/

  Wire.begin();
  mpu6050.begin();
  mpu6050.calcGyroOffsets(true);
}
void loop() {
  delay(50); // Wait 50ms between pings (about 20 pings/sec). 29ms should be the shortest delay between pings.
  
  duration = sonar.ping();
  duration2 = sonar2.ping();
  distance = (duration / 2) * 0.0343;
  distance2 = (duration2 / 2) * 0.0343;
  
  Serial.print("Distance = ");
  Serial.print(distance); // Distance will be 0 when out of set max range.
  Serial.println(" cm");
  Serial.println(" ");
  Serial.print("Distance2 = ");
  Serial.print(distance2);
  Serial.println(" cm");
  Serial.println(" ");
  delay(1000);

  if(distance<20)
  {
    digitalWrite(ledPin,HIGH);
 //   delay(1000);
    digitalWrite(buzzer,HIGH);

  }
  else
  {
    digitalWrite(ledPin,LOW);
  
   digitalWrite(buzzer,LOW);
  }

  if(distance2<20)
  {
    digitalWrite(ledPin2,HIGH);
    digitalWrite(buzzer2,HIGH);
  }
  else
  {
    digitalWrite(ledPin2,LOW);
    digitalWrite(buzzer2,LOW);
  }

  if(millis() - timer > 1000){
    
    Serial.println("=======================================================");
    Serial.print("temp : ");Serial.println(mpu6050.getTemp());
    Serial.print("accX : ");Serial.print(mpu6050.getAccX());
    Serial.print("\taccY : ");Serial.print(mpu6050.getAccY());
    Serial.print("\taccZ : ");Serial.println(mpu6050.getAccZ());
  
    Serial.print("gyroX : ");Serial.print(mpu6050.getGyroX());
    Serial.print("\tgyroY : ");Serial.print(mpu6050.getGyroY());
    Serial.print("\tgyroZ : ");Serial.println(mpu6050.getGyroZ());
  
    Serial.print("accAngleX : ");Serial.print(mpu6050.getAccAngleX());
    Serial.print("\taccAngleY : ");Serial.println(mpu6050.getAccAngleY());
  
    Serial.print("gyroAngleX : ");Serial.print(mpu6050.getGyroAngleX());
    Serial.print("\tgyroAngleY : ");Serial.print(mpu6050.getGyroAngleY());
    Serial.print("\tgyroAngleZ : ");Serial.println(mpu6050.getGyroAngleZ());
    
    Serial.print("angleX : ");Serial.print(mpu6050.getAngleX());
    Serial.print("\tangleY : ");Serial.print(mpu6050.getAngleY());
    Serial.print("\tangleZ : ");Serial.println(mpu6050.getAngleZ());
    Serial.println("=======================================================\n");
    timer = millis();
    
  }
  delay(50);
}
