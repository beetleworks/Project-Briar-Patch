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
  randomSeed(analogRead(A0));
  int minuteTime = random(3, 19); //randomly chooses what minute to play event, between 3 and 18;
  //minuteTime = minuteTime*10; //elongates time of event delay
  Serial.println(minuteTime);
  return minuteTime;
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