char val;
int sensorPin0 = 0;
int sensorPin1 = 1;
int sensorPin2 = 2;
boolean ledState = LOW;
bool lose = false;
bool inWinState = false;
bool inLoseState = false;
const int button1Pin = 2;
const int ledPin =  13;
const int buzzerPin = 10;
int updateCounter = 0;
const int counterSpeed = 30;
int timeLeft = 9;
int nums[11][10]={
               {0,0,0,1,1,1,0,1,1,1},  //0
               {0,0,0,1,0,0,0,0,0,1},  //1
               {0,0,0,0,1,1,1,0,1,1},  //2
               {0,0,0,1,1,0,1,0,1,1},  //3
               {0,0,0,1,0,0,1,1,0,1},  //4
               {0,0,0,1,1,0,1,1,1,0},  //5
               {0,0,0,1,1,1,1,1,1,0},  //6
               {0,0,0,1,0,0,0,0,1,1},  //7
               {0,0,0,1,1,1,1,1,1,1},  //8
               {0,0,0,1,1,0,1,1,1,1},  //9
               {0,0,0,0,0,0,0,0,0,0},};
void writeNum(int);

void setup() {
  Serial.begin(9600);

  pinMode(button1Pin, INPUT);
  pinMode(3,OUTPUT);
  pinMode(4,OUTPUT);
  pinMode(5,OUTPUT);
  pinMode(6,OUTPUT);
  pinMode(7,OUTPUT);
  pinMode(8,OUTPUT);
  pinMode(9,OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  pinMode(ledPin, OUTPUT);
  establishContact();
}

void loop() {
  int delayTime = 100;
  char receiveState = Serial.read();
  if (receiveState == 'l') {
    inLoseState = true;
    tone(buzzerPin, frequency('c'), 450);
  } else if (receiveState == 'w') {
    inWinState = true;
    tone(buzzerPin, frequency('a'), 100);
    delay(150);
    tone(buzzerPin, frequency('a'), 300);
    delay(100);
  }

  if (!inLoseState && !inWinState) {
    lose = false;
    updateCounter++;
    if (updateCounter >= counterSpeed) {
      updateCounter = 0;
      tone(buzzerPin, frequency('e'), 150);
      timeLeft--;
      if (timeLeft <= -2) timeLeft = 9;
    }
    if (timeLeft == 0) {
      tone(buzzerPin, frequency('C'), 150);
      if (updateCounter % 2 == 0) {
        writeNum(timeLeft);
      } else {
        writeNum(10);
      }
    } else if (timeLeft < 0) {
      writeNum(10);
      lose = true;
      inLoseState = true;
    } else writeNum(timeLeft);

    if (lose) {
      tone(buzzerPin, frequency('c'), 450);
      Serial.println("lose");
    }
    char out[80];
    sprintf(out, "%d.%d.%d", analogRead(sensorPin0), analogRead(sensorPin1),
                             analogRead(sensorPin2));
    Serial.println(out);
    delay(delayTime);
  }
  int button1State;

  button1State = digitalRead(button1Pin);

  if (button1State == LOW) {
    reset();
  } else {
   digitalWrite(ledPin, LOW);
   Serial.println("N");
  }
  delay(delayTime);

}

void reset() {
  Serial.println("LR");
  inLoseState = false;
  inWinState = false;
  timeLeft = 9;
  updateCounter = 0;
}

void establishContact() {
  while (Serial.available() <= 0) {
    Serial.println("A");
    delay(300);
  }
}

int frequency(char note)
{
  // This function takes a note character (a-g), and returns the
  // corresponding frequency in Hz for the tone() function.

  int i;
  const int numNotes = 8;  // number of notes we're storing

  // The following arrays hold the note characters and their
  // corresponding frequencies. The last "C" note is uppercase
  // to separate it from the first lowercase "c". If you want to
  // add more notes, you'll need to use unique characters.

  // For the "char" (character) type, we put single characters
  // in single quotes.

  char names[] = { 'c', 'd', 'e', 'f', 'g', 'a', 'b', 'C' };
  int frequencies[] = {262, 294, 330, 349, 392, 440, 494, 523};

  // Now we'll search through the letters in the array, and if
  // we find it, we'll return the frequency for that note.

  for (i = 0; i < numNotes; i++)  // Step through the notes
  {
    if (names[i] == note)         // Is this the one?
    {
      return(frequencies[i]);     // Yes! Return the frequency
    }
  }
  return(0);  // We looked through everything and didn't find it,
              // but we still need to return a value, so return 0.
}

void writeNum(int v){
  for (int i=3;i<=9;i++){
    digitalWrite(i, nums[v][i]);
  }
}
