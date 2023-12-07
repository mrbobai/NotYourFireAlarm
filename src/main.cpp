#include <Arduino.h>

int trigPin = 16; // trig pin d0
int echoPin = 5;  // echo pin d1
int ioPin = 4;    // alarm pin d2
int rPin = 14; // red light pin d5
int gPin = 2; // green light pin d4
int bPin = 0; // blue light pin d3

float duration_us, distance_cm;

void setColor(int R, int G, int B)
{
  analogWrite(rPin, R);
  analogWrite(gPin, G);  
  analogWrite(bPin, B);
}

void beep(int d)
{
  digitalWrite(ioPin, LOW);
  delay(d);
  digitalWrite(ioPin, HIGH);
}

void setup()
{
  // begin serial port
  Serial.begin(9600);

  // configure the trigger pin to output mode
  pinMode(trigPin, OUTPUT);
  // configure the echo pin to input mode
  pinMode(echoPin, INPUT);
  pinMode(ioPin, OUTPUT);
}

void loop()
{
  // generate 10-microsecond pulse to TRIG pin
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // measure duration of pulse from ECHO pin
  duration_us = pulseIn(echoPin, HIGH);

  // calculate the distance
  distance_cm = 0.017 * duration_us;

  // print the value to Serial Monitor
  Serial.print("distance: ");
  Serial.print(distance_cm);
  Serial.println(" cm");
  if (distance_cm < 60) //activate trap
  {
    setColor(255, 255, 255);
    beep(500);
    setColor(255, 0, 0);
  }
  else {
    setColor(0, 0, 0);
  }

  delay(500);
}
