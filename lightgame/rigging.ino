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
    int center = abs(index - 22);

    if (center > 12) return RED;
    else if (center > 4) return YELLOW;
    else if (center >= 1)  return GREEN; 
    else if (center == 0)  return BLUE;

}


int getAdjustment(int projection) {
  int adjustment = 0;
  while (true) {
    if (isViable(projection + adjustment)) return adjustment;
    if (isViable(projection - adjustment)) return -adjustment;
    adjustment += 1;
  }
  
}

bool isViable(int index) {
  Color col = indexToColor(index);

  if (rigMode == RIG_WIN) return col == rigWinColor;

  return rigLoseColors[col];
}