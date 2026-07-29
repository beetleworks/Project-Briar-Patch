bool daytimeDecide (void) {
  int LDRval = analogRead(LDR_Pin);
  int daylightThreshold = 300;
  if (LDRval < daylightThreshold) {
    return true; //daytime
  } else {
    return false; //nighttime
  }
}

int eventDelayer (void) {
  int minuteTime = random(1, 4); // randomly chooses what minute to play event, between 1 and 4-1;
  Serial.println(minuteTime);
  return minuteTime;
}

int eventDecider (void) {
  return random(1,3); //randomly chooses which song to play);
}

bool delayChecker (int starT[2], int currT[2], int evDelay) {
  int minDifference;
  if (currT[0] > starT[0]) {
    minDifference = currT[1] + (60 - starT[1]);
  } else {
    minDifference = currT[1] - starT[1];
  }

  if (minDifference == evDelay) {
    return true;
  } else {
    return false;
  }
}