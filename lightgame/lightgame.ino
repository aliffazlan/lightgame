const int RESETPIN = 0;
const int DSLINITPIN = 0;
const int S0PIN = 0;
const int S1PIN = 0;
const int CLOCKPIN = 0;
const int BUTTONPIN = 0;

const int LED_COUNT = 45;
const int INITIAL_DELAY = 50;
const int TIME_DELTA = 10;
const int INITIAL_STEPS = 60;

const int CLOCK_DELAY = 10;

enum States { IDLE, STARTUP, ACTIVE, SLOW };
States state = IDLE;

enum Modes { SKILL, RIG_LOSE, RIG_WIN };
Modes rigMode = SKILL;

enum Color { RED, YELLOW, GREEN, BLUE };
Color rigWinColor;
bool rigLoseColors[4];

unsigned int timeDelay = INITIAL_DELAY;       

const int totalLEDs = 45;          
int ledPos = 0; 
int direction = 1;

int stepsLeft = 0;




void setup() {
  pinMode(RESETPIN, OUTPUT);
  pinMode(DSLINITPIN, OUTPUT);
  pinMode(S0PIN, OUTPUT);
  pinMode(S1PIN, OUTPUT);
  pinMode(CLOCKPIN, OUTPUT);
  pinMode(BUTTONPIN, INPUT); 


  rigMode = SKILL;
  resetGame();
}


void loop() {
  switch(state) {

    case IDLE:
      if (buttonPressed()) {
        resetGame();
        timeDelay = INITIAL_DELAY;
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
        stepsLeft = INITIAL_STEPS + getAdjustment(projectWinningLED(ledPos, direction));
      }
      break;

    case SLOW:
      shiftLED();
      if (stepsLeft <= 0) {
        state = IDLE;
      }
      stepsLeft -= 1;
      timeDelay += TIME_DELTA;
      break;
  }
}

bool buttonPressed() {
  if (digitalRead(BUTTONPIN)) {
    delay(50);
    return digitalRead(BUTTONPIN);
  }
  return false;
}

void clockPulse() {
  delay(CLOCK_DELAY);
  digitalWrite(CLOCKPIN, HIGH);
  delay(CLOCK_DELAY);
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

