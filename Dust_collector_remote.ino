/*
  
*/

// constants won't change. They're used here to set pin numbers:
const int DCbuttonPin = 2;    // the number of the pushbutton pin
const int DCledPin = 3;      // the number of the LED pin
const int DCpowerPin = 4;      // the number of the LED pin
const long intervalblink = 1000;           // interval at which to blink (milliseconds)
const long intervalflash = 100;           // interval at which to blink (milliseconds)
const long intervalcountdown = 30000;           // timer to shut down machine (milliseconds)
const long intervalwarning = 15000;           // rapidly flashes before shutting dolwn (milliseconds)


// Variables will change:
int DCledState = LOW;         // the current state of the output pin
int DCbuttonState;             // the current reading from the input pin
int lastDCButtonState = LOW;   // the previous reading from the input pin
int DCpowerState = false;   // 

// the following variables are unsigned longs because the time, measured in
// milliseconds, will quickly become a bigger number than can be stored in an int.
unsigned long lastDebounceTime = 0;  // the last time the output pin was toggled
unsigned long debounceDelay = 50;    // the debounce time; increase if the output flickers
unsigned long holdDelay = 500;    // hold to activate second setting
unsigned long previousMillis = 0;   // will store last time LED was updated
unsigned long lastDCTime = 0;  // the last time the DCState was changed to true



void setup() {
  pinMode(DCbuttonPin, INPUT);
  pinMode(DCledPin, OUTPUT);
  pinMode(DCpowerPin, OUTPUT);

  // set initial LED state
  digitalWrite(DCledPin, DCledState);
}

void loop() {
  // read the state of the switch into a local variable:
  int reading = digitalRead(DCbuttonPin);

  // check to see if you just pressed the button
  // (i.e. the input went from LOW to HIGH), and you've waited long enough
  // since the last press to ignore any noise:

  // If the switch changed, due to noise or pressing:
  if (reading != lastDCButtonState) {
    // reset the debouncing timer
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay < holdDelay) {
    // whatever the reading is at, it's been there for longer than the debounce
    // delay, so take it as the actual current state:

    // if the button state has changed:
    if (reading != DCbuttonState) {
      DCbuttonState = reading;

      // only toggle the DCState if the new button state is HIGH, and reset timer
      if (DCbuttonState == HIGH) {
        DCpowerState = true;
        lastDCTime = millis();
      }
    }
  } else if ((millis() - lastDebounceTime) > debounceDelay > holdDelay) {
        // if the button state has changed:
    if (reading != DCbuttonState) {
      DCbuttonState = reading;

      // only toggle the DCState if the new button state is HIGH, and reset timer
      if (DCbuttonState == HIGH) {
        DCpowerState = true;
        lastDCTime = (millis() + 1800000);
      }
    }
  }

  // save the reading. Next time through the loop, it'll be the lastDCButtonState:
  lastDCButtonState = reading;

  // defines DCpowerState:
  if (DCpowerState == true) {
    digitalWrite(DCledPin, DCledState);
    digitalWrite(DCpowerPin, HIGH);
  }
  if (DCpowerState == false) {
    digitalWrite(DCledPin, LOW);
    digitalWrite(DCpowerPin, LOW);
  }

 if ((millis() - lastDCTime) > intervalcountdown) {
    DCpowerState = false; 
 }
 if ((millis() - lastDCTime) > 0 < intervalwarning) {
    if ((millis() - previousMillis) >= intervalblink) {
    
    previousMillis = millis(); //save the last time it blinked

      if (DCledState == LOW) {
      DCledState = HIGH;
      } else {
      DCledState = LOW;
      }
    
    }}   
    if ((millis() - lastDCTime) > intervalwarning) {
      if ((millis() - previousMillis) >= intervalflash) {
    
    previousMillis = millis();
  
    if (DCledState == LOW) {
      DCledState = HIGH;
    } else {
      DCledState = LOW;
    }
  }
    }

  }
