const int ledPin = 13;

const int ldrPin = A0;

void setup() {

  Serial.begin(9600);  
  pinMode(ledPin, OUTPUT);
  pinMode(ldrPin, INPUT);

}

void loop() {

  int ldrStatus = analogRead(ldrPin);  
  if (ldrStatus <= 200) {
    digitalWrite(ledPin, LOW);  
    Serial.print("Its BRIGHT, Turn on the LED : ");
    Serial.println(ldrStatus);  
  } else {
    digitalWrite(ledPin, HIGH);  
    Serial.print("Its DARK, Turn off the LED : ");
    Serial.println(ldrStatus);  
  }

}
