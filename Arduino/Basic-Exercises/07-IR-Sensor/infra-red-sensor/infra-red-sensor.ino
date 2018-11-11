void setup() {
  // put your setup code here, to run once:
  pinMode(7,OUTPUT);

  pinMode(8,INPUT); 
}

void loop() {
  // put your main code here, to run repeatedly:
//  digitalWrite(7,HIGH);
  int detect = digitalRead(8);
  if (detect) {
    digitalWrite(7,HIGH);    
  } else {
      digitalWrite(7,LOW);
  }

  delay(300);
}
