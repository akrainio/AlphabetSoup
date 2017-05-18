char val;
int sensorPin = 0;
boolean ledState = LOW;
const int button1Pin = 2;
const int button2Pin = 3;
const int ledPin =  13;

void setup() {
  Serial.begin(9600);
  establishContact();
  pinMode(button1Pin, INPUT);
  pinMode(button2Pin, INPUT);

  // Set up the LED pin to be an output:
  pinMode(ledPin, OUTPUT);
}

void loop() {
  int delayTime = 100;

  Serial.println(analogRead(sensorPin));
  delay(delayTime);

  int button1State, button2State;

  button1State = digitalRead(button1Pin);
  button2State = digitalRead(button2Pin);

  if ((button1State == LOW) && (button2State == LOW)) {
   digitalWrite(ledPin, HIGH);
   Serial.println("LR");
  } else if (button1State == LOW) {
   digitalWrite(ledPin, HIGH);
   Serial.println("L");
  } else if (button2State == LOW) {
   digitalWrite(ledPin, HIGH);
   Serial.println("R");
  } else {
   digitalWrite(ledPin, LOW);
   Serial.println("N");
  }
  delay(delayTime);
}

void establishContact() {
  while (Serial.available() <= 0) {
    Serial.println("A");
    delay(300);
  }
}
