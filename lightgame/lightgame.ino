int RESETPIN = 0;
int DSLINITPIN = 0;
int S0PIN = 0;
int S1PIN = 0;
int CLOCKPIN = 0;
int BUTTONPIN = 0;

enum States { IDLE, STARTUP, ACTIVE, SLOW };
States state = IDLE;

unsigned int timeDelay = 10;       
const unsigned int MAX_DELAY = 1000; 

const int totalLEDs = 45;          
int ledPos = 0; 
int direction = 1;


void setup() {
  pinMode(RESETPIN, OUTPUT);
  pinMode(DSLINITPIN, OUTPUT);
  pinMode(S0PIN, OUTPUT);
  pinMode(S1PIN, OUTPUT);
  pinMode(CLOCKPIN, OUTPUT);
  pinMode(BUTTONPIN, INPUT); 

  resetGame();
}


void loop() {
  switch(state) {

    case IDLE:
      if (buttonPressed()) {
        resetGame();
        timeDelay = 10;
        state = STARTUP;
      }
      break;

    case STARTUP:
      startupSequence();
      ledPos = 0;
      direction = 1;
      state = ACTIVE;
      break;

    case ACTIVE:
      shiftLED();
      if (buttonPressed()) {
        state = SLOW;
      }
      break;

    case SLOW:
      shiftLED();
      timeDelay += 10;
      if (timeDelay >= MAX_DELAY) {
        state = IDLE;
      }
      break;
  }
}

bool buttonPressed() {
  if digitalRead(BUTTONPIN) {
    delay(50);
    return digitalRead(BUTTONPIN);
  }
  return false;
}

void clockPulse() {
  delay(timeDelay);
  digitalWrite(CLOCKPIN, HIGH);
  delay(timeDelay);
  digitalWrite(CLOCKPIN, LOW);
}


void setShiftLeft() {
  digitalWrite(S1PIN, HIGH);
  digitalWrite(S0PIN, LOW);
}

void setShiftRight() {
  digitalWrite(S1PIN, LOW);
  digitalWrite(S0PIN, HIGH);
}


void startupSequence() {
  digitalWrite(DSLINITPIN, HIGH);
  setShiftLeft();
  for (int i = 0; i < totalLEDs; i++) {
    clockPulse();
  }
  delay(200);

  setShiftRight();
  for (int i = 0; i < totalLEDs; i++) {
    clockPulse();
  }
  delay(200);

  setShiftLeft();
  clockPulse();
}



void shiftLED() {
  if (direction == 1) {
    setShiftLeft();
  } else {
    setShiftRight();
  }
  clockPulse();
  
  ledPos += direction;
  if (ledPos >= totalLEDs - 1) {
    direction = -1;
    ledPos = totalLEDs - 1;
  } else if (ledPos <= 0) {
    direction = 1;
    ledPos = 0;
  }
}

void resetGame() {
  delay(10);
  digitalWrite(RESETPIN, LOW);
  delay(50);
  digitalWrite(RESETPIN, HIGH);
  delay(50);
}