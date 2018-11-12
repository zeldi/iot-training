void setup() {
  // put your setup code here, to run once:
  pinMode(7,OUTPUT);

  pinMode(A2,INPUT); 
  pinMode(A1,OUTPUT); 
  pinMode(A0,OUTPUT); 

  digitalWrite(A1,LOW);  // Sensor GND 
  digitalWrite(A0,HIGH); // Supply 5v 
  digitalWrite(7,LOW);

  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
//  digitalWrite(7,HIGH);
//  int detect = digitalRead(8);
//  if (analogRead(A2) < 500) {
//    digitalWrite(7,HIGH);    
//  } else {
//      digitalWrite(7,LOW);
//  }
  Serial.println(analogRead(A0));
  delay(300);
}
