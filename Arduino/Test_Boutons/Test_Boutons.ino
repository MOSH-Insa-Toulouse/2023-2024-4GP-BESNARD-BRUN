
#define baudrate 9600 
#include <SoftwareSerial.h>


// constants won't change. They're used here to set pin numbers:
const int buttonPin[] = {6,5,4};  // the number of the pushbutton pin



const int ledPin = 13;    // the number of the LED pin

// Variables will change:
int ledState = HIGH;        // the current state of the output pin
int buttonState[3];            // the current reading from the input pin
int lastButtonState[3] = {LOW,LOW,LOW};  // the previous reading from the input pin
int reading[3];

// the following variables are unsigned longs because the time, measured in
// milliseconds, will quickly become a bigger number than can be stored in an int.
unsigned long lastDebounceTime = 0;  // the last time the output pin was toggled
unsigned long debounceDelay = 50;    // the debounce time; increase if the output flickers

void setup() {
  pinMode(buttonPin[0], INPUT);
  pinMode(buttonPin[1], INPUT);
  pinMode(buttonPin[2], INPUT);
  pinMode(ledPin, OUTPUT);

  // set initial LED state
  digitalWrite(ledPin, ledState);

  Serial.begin(baudrate); // Initialiser le port série
}

void loop() {
  reading[0] = digitalRead(buttonPin[0]);
  digitalWrite(ledPin, reading[0]);
  Serial.println(reading[0]);
  // // read the state of the switch into a local variable:
  // for (int i = 0; i < 3; i++) {
  //   reading[i] = digitalRead(buttonPin[i]);
  

  // // check to see if you just pressed the button
  // // (i.e. the input went from LOW to HIGH), and you've waited long enough
  // // since the last press to ignore any noise:

  // // If the switch changed, due to noise or pressing:
  // if (reading[i] != lastButtonState[i]) {
  //   // reset the debouncing timer
  //   lastDebounceTime = millis();
  // }

  // if ((millis() - lastDebounceTime) > debounceDelay) {
  //   // whatever the reading is at, it's been there for longer than the debounce
  //   // delay, so take it as the actual current state:

  //   // if the button state has changed:
  //   if (reading[i] != buttonState[i]) {
  //     buttonState[i] = reading[i];

  //     // only toggle the LED if the new button state is HIGH
  //     if (buttonState[i] == HIGH) {
  //       ledState = !ledState;
  //     }
  //   }
  // }
  
  // // set the LED:
  // digitalWrite(ledPin, ledState);

  // // save the reading. Next time through the loop, it'll be the lastButtonState:
  // lastButtonState[i] = reading[i];
  // }
}
