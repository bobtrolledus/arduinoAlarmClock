#include "pitches.h"
#include "segmentDisplay.h"
#include <Servo.h>

//Creates vars for all outputs
Servo myServo;
int buttonPin = 2;
int buzzerPin = 11;
int ledPin = 12;

//Creates vars for all inputs
int potPin = 0;

//Creates vars for all logic
int buttonState = 0;
int potValue = 0;
volatile byte state = LOW;
volatile byte lastButtonState = LOW;
unsigned long currentMillis;
unsigned long blinkMillis;
unsigned long minMillis;
unsigned long previousMillis = 0; 
const long interval = 1000;  
int ledState = LOW;
 
void setup() {
  pinMode(a, OUTPUT);
  pinMode(b, OUTPUT);
  pinMode(c, OUTPUT);
  pinMode(d, OUTPUT);
  pinMode(e, OUTPUT);
  pinMode(f, OUTPUT);
  pinMode(g, OUTPUT);

  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(buttonPin), submitValue, RISING);
  myServo.attach(10);

  Serial.begin(9600);
}

void submitValue()
{
  state != state;
  lastButtonState = HIGH;
}

void loop() {
  myServo.write(0);
  digitalWrite(ledPin, LOW);
  potValue = analogRead(potPin);
  potValue = map(potValue, 0, 1023, 1, 5);
  buttonState = digitalRead(buttonPin);

  //Outputs number on 7 segment according to read and mapped potentiometer value
  if(potValue == 1)
  {
    digitOne();
  }
  else if(potValue == 2)
  {
    digitTwo();
  }
  else if(potValue == 3)
  {
    digitThree();
  }
  else if(potValue == 4)
  {
    digitFour();
  }
  else if(potValue == 5)
  {
    digitFive();
  }
  
  if(lastButtonState != state)
  {
    //reads current time button was pressed
    currentMillis = millis();
    minMillis = (currentMillis + (potValue * 60000));
    
    //blinks led every second
    while(millis() < minMillis)
    {
      unsigned long currentMillis = millis();
      if (currentMillis - previousMillis >= interval) 
      {
        previousMillis = currentMillis;
        
        if (ledState == LOW) {
          ledState = HIGH;
        } else {
          ledState = LOW;
        }
      
        digitalWrite(ledPin, ledState);
      }
    }

    //Turns servo and turns LED on/off
    digitalWrite(ledPin, HIGH);
    myServo.write(180);
    delay(3000);
    myServo.write(0);
    digitalWrite(ledPin, LOW);
    clearAll();

    //Beeps buzzerr 5 times at C4 tonation
    for(int i = 0; i < 5; i++)
    {
      tone(buzzerPin, NOTE_C4, (1000/4));
      int pauseBetweenNotes = (1000/4) * 1.30;
      delay(pauseBetweenNotes);
      noTone(buzzerPin);
    }

    lastButtonState = LOW;
    
  }
  Serial.println("I am not running");
}
