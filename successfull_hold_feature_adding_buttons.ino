/*
  
*/

// constants won't change. They're used here to set pin numbers:
const int DCbuttonPin = 2;    // the number of the pushbutton pin
const int DCledPin = 3;      // the number of the LED pin
const int DCpowerPin = 4;      // the number of the LED pin
const int VACbuttonPin = 5;
const int VACledPin = 6;
const int VACpowerPin = 7;
const int STOPbuttonPin = 8;
const int STOPledPin = 9;
const long intervalblink = 1000;           // interval at which to blink (milliseconds)
const long intervalflash = 100;           // interval at which to blink (milliseconds)
const long intervalcountdown = 30000;           // timer to shut down machine (milliseconds)
const long intervalwarning = 15000;           // rapidly flashes before shutting down (milliseconds)
const long intervalhold = 1800000;

// Variables will change:
int DCledState = LOW;         // the current state of the output pin
int DCbuttonState;             // the current reading from the input pin
int lastDCbuttonState = LOW;   // the previous reading from the input pin
int DCpowerState = false;   // 
int DCholdState = false;
int VACledState = LOW;         // the current state of the output pin
int VACbuttonState;             // the current reading from the input pin
int lastVACbuttonState = LOW;   // the previous reading from the input pin
int VACpowerState = false;   // 
int VACholdState = false;
int STOPledState = LOW;
int STOPbuttonState;
int lastSTOPbuttonState = LOW;

// the following variables are unsigned longs because the time, measured in
// milliseconds, will quickly become a bigger number than can be stored in an int.
unsigned long lastDCDebounceTime = 0;  // the last time the output pin was toggled
unsigned long lastVACDebounceTime = 0;  // the last time the output pin was toggled
unsigned long debounceDelay = 50;    // the debounce time; increase if the output flickers
unsigned long holdDelay = 500;    // hold to activate second setting
unsigned long previousDCMillis = 0;   // will store last time LED was updated
unsigned long lastDCTime = 0;  // the last time the DCpowerState was changed to true
unsigned long previousVACMillis = 0;   // will store last time LED was updated
unsigned long lastVACTime = 0;  // the last time the VACpowerState was changed to true
unsigned long lastSTOPDebounceTime = 0;




void setup() {
  pinMode(DCbuttonPin, INPUT);
  pinMode(DCledPin, OUTPUT);
  pinMode(DCpowerPin, OUTPUT);
  pinMode(VACbuttonPin, INPUT);
  pinMode(VACledPin, OUTPUT);
  pinMode(VACpowerPin, OUTPUT);
  pinMode(STOPbuttonPin, INPUT);
  pinMode(STOPledPin, OUTPUT);
  

  // set initial LED state
  digitalWrite(DCledPin, DCledState);
  digitalWrite(VACledPin, VACledState);
  digitalWrite(STOPledPin, STOPledState);
}

void loop() {
  // read the state of the switch into a local variable:
  int readingDC = digitalRead(DCbuttonPin);
  int readingVAC = digitalRead(VACbuttonPin);
  int readingSTOP = digitalRead(STOPbuttonPin);

  // check to see if you just pressed the button
  // (i.e. the input went from LOW to HIGH), and you've waited long enough
  // since the last press to ignore any noise:

  // If the switch changed, due to noise or pressing:
  if (readingDC != lastDCbuttonState) {
    // reset the debouncing timer
    lastDCDebounceTime = millis();
  }

  if ((millis() - lastDCDebounceTime) > debounceDelay) {
    // whatever the reading is at, it's been there for longer than the debounce
    // delay, so take it as the actual current state:

    // if the button state has changed:
    if (readingDC != DCbuttonState) {
      DCbuttonState = readingDC;

      // only toggle the DCState if the new button state is HIGH, and reset timer
      if (DCbuttonState == HIGH) {
        DCpowerState = true;
        DCholdState = false;
        lastDCTime = millis();
     }
    
        if ((DCbuttonState == LOW) && (DCpowerState == true) && ((millis() - lastDCTime) > holdDelay)){
          DCholdState = true;

        }
      
     }
  }

  // save the reading. Next time through the loop, it'll be the lastDCbuttonState:
  lastDCbuttonState = readingDC;

  // defines DCpowerState:
  if (DCpowerState == true) {
    digitalWrite(DCledPin, DCledState);
    digitalWrite(DCpowerPin, HIGH);
  }
  if (DCpowerState == false) {
    digitalWrite(DCledPin, LOW);
    digitalWrite(DCpowerPin, LOW);
  }

 if (DCholdState == true) {
    DCpowerState = false;                                                                                                                                                                                                                                                      
    digitalWrite(DCledPin, HIGH);
    digitalWrite(DCpowerPin, HIGH);
}

if ((millis() - lastDCTime) > intervalcountdown) {
    DCpowerState = false; 
 }
 if ((millis() - lastDCTime) < intervalwarning) {
    if ((millis() - previousDCMillis) >= intervalblink) {
    
    previousDCMillis = millis(); //save the last time it blinked

      if (DCledState == LOW) {
      DCledState = HIGH;
      } else {
      DCledState = LOW;
      }
    
    }}   
    if ((millis() - lastDCTime) > intervalwarning) {
      if ((millis() - previousDCMillis) >= intervalflash) {
    
    previousDCMillis = millis();
  
    if (DCledState == LOW) {
      DCledState = HIGH;
    } else {
      DCledState = LOW;
    }
  }
    }
if ((DCholdState == true) && ((millis() - lastDCTime) > intervalhold)) {
    DCpowerState = true;
    lastDCTime = millis();
    DCholdState = false;
    }
      // If the switch changed, due to noise or pressing:
  if (readingVAC != lastVACbuttonState) {
    // reset the debouncing timer
    lastVACDebounceTime = millis();
  }

  if ((millis() - lastVACDebounceTime) > debounceDelay) {
    // whatever the reading is at, it's been there for longer than the debounce
    // delay, so take it as the actual current state:

    // if the button state has changed:
    if (readingVAC != VACbuttonState) {
      VACbuttonState = readingVAC;

      // only toggle the VACState if the new button state is HIGH, and reset timer
      if (VACbuttonState == HIGH) {
        VACpowerState = true;
        VACholdState = false;
        lastVACTime = millis();
     }
    
        if ((VACbuttonState == LOW) && (VACpowerState == true) && ((millis() - lastVACTime) > holdDelay)){
          VACholdState = true;

        }
      
     }
  }

  // save the reading. Next time through the loop, it'll be the lastVACbuttonState:
  lastVACbuttonState = readingVAC;

  // defines VACpowerState:
  if (VACpowerState == true) {
    digitalWrite(VACledPin, VACledState);
    digitalWrite(VACpowerPin, HIGH);
  }
  if (VACpowerState == false) {
    digitalWrite(VACledPin, LOW);
    digitalWrite(VACpowerPin, LOW);
  }

 if (VACholdState == true) {
    VACpowerState = false;                                                                                                                                                                                                                                                      
    digitalWrite(VACledPin, HIGH);
    digitalWrite(VACpowerPin, HIGH);
}

if ((millis() - lastVACTime) > intervalcountdown) {
    VACpowerState = false; 
 }
 if ((millis() - lastVACTime) < intervalwarning) {
    if ((millis() - previousVACMillis) >= intervalblink) {
    
    previousVACMillis = millis(); //save the last time it blinked

      if (VACledState == LOW) {
      VACledState = HIGH;
      } else {
      VACledState = LOW;
      }
    
    }}   
    if ((millis() - lastVACTime) > intervalwarning) {
      if ((millis() - previousVACMillis) >= intervalflash) {
    
    previousVACMillis = millis();
  
    if (VACledState == LOW) {
      VACledState = HIGH;
    } else {
      VACledState = LOW;
    }
  }
    }
if ((VACholdState == true) && ((millis() - lastVACTime) > intervalhold)) {
    VACpowerState = true;
    lastVACTime = millis();
    VACholdState = false;
    }
if (readingSTOP != lastSTOPbuttonState) {
    // reset the debouncing timer
    lastSTOPDebounceTime = millis();
  }

  if ((millis() - lastSTOPDebounceTime) > debounceDelay) {
    // whatever the reading is at, it's been there for longer than the debounce
    // delay, so take it as the actual current state:

    // if the button state has changed:
    if (readingSTOP != STOPbuttonState) {
      STOPbuttonState = readingSTOP;

      // only toggle the STOPState if the new button state is HIGH, and reset timer
      if (STOPbuttonState == HIGH) {
        DCpowerState = false;
        DCholdState = false;
        VACpowerState = false;
        VACholdState = false;
        lastDCTime = 0;
        lastVACTime = 0;
     }
  }
  }
  
  lastSTOPbuttonState = readingSTOP;
  
  if ((DCpowerState == true) || (VACpowerState == true) || (DCholdState == true) || (VACholdState == true)) {
    digitalWrite (STOPledPin, HIGH);
  } 
  if ((DCpowerState == false) && (VACpowerState == false) && (DCholdState == false) && (VAChold  2State == false)) {
    digitalWrite (STOPledPin, LOW);
  } 
  }
    

  
