int eyePin = 2;
int buzzer = 8;
int led = 13;

unsigned long eyeClosedTime = 0;
bool eyeClosed = false;

void setup() {
  pinMode(eyePin, INPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(led, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  int eyeState = digitalRead(eyePin);

  if (eyeState == LOW) { // Eye Closed
    if (!eyeClosed) {
      eyeClosed = true;
      eyeClosedTime = millis();
    }
    
    if (millis() - eyeClosedTime > 2000) {
      digitalWrite(buzzer, HIGH);
      digitalWrite(led, HIGH);
    }
  } 
  else { // Eye Open
    eyeClosed = false;
    digitalWrite(buzzer, LOW);
    digitalWrite(led, LOW);
  }

  delay(100);
}
