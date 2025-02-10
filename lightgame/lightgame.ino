const int RESETPIN = 7;
const int DSLINITPIN = 8;
const int S0PIN = 4;
const int S1PIN = 5;
const int CLOCKPIN = 6;
const int BUTTONPIN = 10;
const int BUTTONLED = 9;

const int LED_COUNT = 32;
const int INITIAL_DELAY = 9;
const int TIME_DELTA = 4;
const int INITIAL_STEPS = 45;

const int STARTUPCOUNT = 7;

enum States { IDLE, STARTUP, ACTIVE, SLOW };
States state = IDLE;

enum Modes { SKILL, RIG_LOSE, RIG_WIN };
Modes rigMode = SKILL;

enum Color { RED, YELLOW, GREEN, BLUE };
Color rigWinColor;
bool rigLoseColors[4];

unsigned int timeDelay = INITIAL_DELAY;       

const int totalLEDs = 31;          
int ledPos = 0; 
int direction = 1;

int stepsLeft = 0;




void setup() {
  Serial.begin(9600);
  pinMode(RESETPIN, OUTPUT);
  pinMode(DSLINITPIN, OUTPUT);
  pinMode(S0PIN, OUTPUT);
  pinMode(S1PIN, OUTPUT);
  pinMode(CLOCKPIN, OUTPUT);
  pinMode(BUTTONPIN, INPUT); 
  pinMode(BUTTONLED, OUTPUT);


  rigMode = SKILL;
  resetGame();
  digitalWrite(BUTTONLED, HIGH);
  Serial.println("READY");
}


void loop() {
  switch(state) {

    case IDLE:
      readInput();
      if (buttonPressed()) {
        //Serial.println("BUTTON");
        resetGame();
        timeDelay = INITIAL_DELAY;
        state = STARTUP;
        digitalWrite(BUTTONLED, LOW);
      }
      break;

    case STARTUP:
      //Serial.println("STARTUP");
      startupSequence();
      ledPos = 0;
      direction = 1;
      state = ACTIVE;
      digitalWrite(BUTTONLED, HIGH);
      //Serial.println("STARTUP FINISHED");
      break;

    case ACTIVE:
      shiftLED();
      if (buttonPressed()) {
        //Serial.println("BUTTON");
        state = SLOW;
        stepsLeft = INITIAL_STEPS + getAdjustment(projectWinningLED(ledPos, direction)) - 1;
        digitalWrite(BUTTONLED, LOW);
        //Serial.println("SLOW");
        
      }
      break;

    case SLOW:
      shiftLED();
      if (stepsLeft <= 0) {
        state = IDLE;
        digitalWrite(BUTTONLED, HIGH);
        //Serial.println("STOP");
      }
      stepsLeft -= 1;
      timeDelay += TIME_DELTA;
      break;
  }
}

bool buttonPressed() {
  // if (digitalRead(BUTTONPIN)) {
  //   delay(50);
  //   return digitalRead(BUTTONPIN);
  // }
  // return false;
  return digitalRead(BUTTONPIN);
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
  timeDelay = 13;
  digitalWrite(DSLINITPIN, HIGH);
  setShiftRight();
  for (int i = 0; i < STARTUPCOUNT; i++) {
    clockPulse();
  }
  digitalWrite(DSLINITPIN, LOW);

  for (int i = 0; i < (totalLEDs / 2) - (STARTUPCOUNT / 2); i++) {
    clockPulse();
  }
  delay(1000);
  for (int i = 0; i < (totalLEDs / 2) + (STARTUPCOUNT / 2) + 2; i++) {
    clockPulse();
  }

  
  
  delay(200);

  resetGame();
  digitalWrite(DSLINITPIN, HIGH);
  timeDelay = INITIAL_DELAY;

  setShiftRight();
  clockPulse();

  digitalWrite(DSLINITPIN, LOW);
}



void shiftLED() {
  // if (direction == 1) {
  //   setShiftRight();
  // } else {
  //   setShiftLeft();
  // }
  clockPulse();
  
  ledPos += direction;
  if (ledPos > totalLEDs - 1) {
    direction = -1;
    setShiftLeft();
  } else if (ledPos <= 0) {
    direction = 1;
    setShiftRight();
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

