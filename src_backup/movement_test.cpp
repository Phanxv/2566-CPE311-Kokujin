#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver myServo = Adafruit_PWMServoDriver();

#define SERVOMIN 150
#define SERVOMAX 600

uint8_t servonum = 0;
uint8_t numberOfServos = 3;

int ENA_pin = 32, IN1_pin = 33, IN2_pin = 25;

void setup() {
  Serial.begin(9600);
  pinMode(ENA_pin, OUTPUT);
  pinMode(IN1_pin, OUTPUT);
  pinMode(IN2_pin, OUTPUT);
  digitalWrite(ENA_pin, LOW);
  digitalWrite(IN1_pin, LOW);
  digitalWrite(IN2_pin, LOW);
  myServo.begin();
  myServo.setPWMFreq(50);
  delay(10);
}

void loop() {
  for (uint16_t pulselen = SERVOMIN; pulselen < SERVOMAX; pulselen++){
    myServo.setPWM(servonum, 0, pulselen);
    delay(5);
  }
  delay(500);
  for (uint16_t pulselen = SERVOMAX; pulselen > SERVOMIN; pulselen--){
    myServo.setPWM(servonum, 0, pulselen);
    delay(5);
  }
  delay(500);
  digitalWrite(ENA_pin, HIGH);
  digitalWrite(IN1_pin, HIGH);
  digitalWrite(IN2_pin, LOW);
  delay(1000);
  digitalWrite(ENA_pin, LOW);
  digitalWrite(IN1_pin, LOW);
  digitalWrite(IN2_pin, LOW);
  delay(1000);
  servonum++;
  if (servonum > numberOfServos-1) 
     servonum = 0;
}