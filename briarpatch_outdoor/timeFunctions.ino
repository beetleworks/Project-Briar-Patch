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
  int minuteTime = random(2, 4); //randomly chooses what minute to play event, between 3 and 18;
  //minuteTime = minuteTime*10; //elongates time of event delay
  Serial.print("Minute Delay: ");
  Serial.println(minuteTime);
  return minuteTime;
}

bool delayChecker (void) {
  rtc.refresh();
  int currT[2];
  currT[0] = rtc.hour();
  currT[1] = rtc.minute();
  int minDifference;
  minDifference = ((currT[0]*60) + currT[1]) - ((startTime[0]*60) + startTime[1]);
  //Serial.print("MinDiff: ");
  //Serial.println(minDifference);

  if (minDifference >= eventDelay) {
    return true;
  } else {
    return false;
  }
}