void setup() {
  // put your setup code here, to run once:
  pinMode(13,OUTPUT);

  pinMode(A2,INPUT); 
  pinMode(A1,OUTPUT); 
  pinMode(A0,OUTPUT); 

  digitalWrite(A1,LOW);  // Sensor GND 
  digitalWrite(A0,HIGH); // Supply 5v 
  digitalWrite(13,LOW);
  
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:

  Serial.println(analogRead(A2));
  delay(300);

//  digitalWrite(7,HIGH);
//  int detect = digitalRead(8);
  if (analogRead(A2) > 600) {
    digitalWrite(13,HIGH);    
  } else {
      digitalWrite(13,LOW);
  }
}
