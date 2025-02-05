

void readInput() {
  if (Serial.available()) {
    String input = Serial.readString();
    input.trim();
    if (input.equalsIgnoreCase("SKILL")) {
      rigMode = SKILL;
      Serial.println("SKILL MODE");
    } else if (input.equalsIgnoreCase("RIG_RED")) {
      rigMode = RIG_WIN;
      rigWinColor = RED;
      Serial.println("RIGGED TO LAND ON RED");
    } else if (input.equalsIgnoreCase("RIG_YELLOW")) {
      rigMode = RIG_WIN;
      rigWinColor = YELLOW;
      Serial.println("RIGGED TO LAND ON GREEN");
    } else if (input.equalsIgnoreCase("RIG_GREEN")) {
      rigMode = RIG_WIN;
      rigWinColor = GREEN;
      Serial.println("RIGGED TO LAND ON GREEN");
    } else if (input.equalsIgnoreCase("RIG_BLUE")) {
      rigMode = RIG_WIN;
      rigWinColor = BLUE;
      Serial.println("RIGGED TO LAND ON BLUE");
    } else if (input.equalsIgnoreCase("TOGGLE_RED")) {
      rigLoseColors[RED] = !rigLoseColors[RED];
      Serial.print("RED ");
      Serial.println(boolStatus(rigLoseColors[RED]));
    } else if (input.equalsIgnoreCase("TOGGLE_YELLOW")) {
      rigLoseColors[YELLOW] = !rigLoseColors[YELLOW];
      Serial.print("YELLOW ");
      Serial.println(boolStatus(rigLoseColors[YELLOW]));
    } else if (input.equalsIgnoreCase("TOGGLE_GREEN")) {
      rigLoseColors[GREEN] = !rigLoseColors[GREEN];
      Serial.print("GREEN ");
      Serial.println(boolStatus(rigLoseColors[GREEN]));
    } else if (input.equalsIgnoreCase("TOGGLE_BLUE")) {
      rigLoseColors[BLUE] = !rigLoseColors[BLUE];
      Serial.print("BLUE ");
      Serial.println(boolStatus(rigLoseColors[BLUE]));
    } else {
      Serial.println("u stink");
    }
    
  }
}

String boolStatus(bool b) {
  return b ? "ENABLED" : "DISABLED";
}