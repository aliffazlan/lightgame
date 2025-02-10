int projectWinningLED(int current, int direction) {
    //int steps = (FINAL_DELAY - INITIAL_DELAY) / TIME_DELTA;
    int steps = INITIAL_STEPS;
    
    int period = 2 * (LED_COUNT - 1);
    
    int S = current + steps * direction;
    
    S = S % period;
    if (S < 0) {
        S += period;
    }
    
    if (S > LED_COUNT - 1) {
        S = period - S;
    }
    
    return S;
}

Color indexToColor(int index) {
    if (index <= 6) return RED;
    else if (index <= 11) return YELLOW;
    else if (index <= 14) return GREEN;
    else if (index <= 16) return BLUE;
    else if (index <= 19) return GREEN;
    else if (index <= 24) return YELLOW;
    else return RED;

}


int getAdjustment(int projection) {
  int adjustment = 0;
  while (true) {
    adjustment += 1;
    if (isViable(projection + adjustment)) return adjustment;
    if (isViable(projection - adjustment)) return -adjustment;
    
  }
  
}

bool isViable(int index) {
  Color col = indexToColor(index);

  if (rigMode == RIG_WIN) return col == rigWinColor;

  return !rigLoseColors[col];
}