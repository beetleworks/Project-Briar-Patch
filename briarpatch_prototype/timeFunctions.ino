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

bool delayChecker (void) {
  int currT[2];
  currT[0] = rtc.hour();
  currT[1] = rtc.minute();
  int minDifference;
  if (currT[0] > startTime[0]) {
    minDifference = currT[1] + (60 - startTime[1]);
  } else {
    minDifference = currT[1] - startTime[1];
  }

  if (minDifference == eventDelay) {
    return true;
  } else {
    return false;
  }
}