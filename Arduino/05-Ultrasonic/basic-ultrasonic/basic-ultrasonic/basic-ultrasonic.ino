/*
HC-SR04 Ping distance sensor]
VCC  --> arduino 5v 
GND  --> arduino GND
Echo --> Arduino pin 2 
Trig --> Arduino pin 3
*/

#define trigPin 3
#define echoPin 2
#define led 13

void setup() {
  Serial.begin (9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(led, OUTPUT);
}

void loop() {
  
  long duration, distance;
  
  //Clear the trigPin
  digitalWrite(trigPin, LOW);  
  delayMicroseconds(2); 
  
  // The trigPin is required to be set to HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  duration = pulseIn(echoPin, HIGH);
  distance = (duration/2) / 29.1;

  Serial.print(distance);
  Serial.println(" cm");

  delay(500);
}
