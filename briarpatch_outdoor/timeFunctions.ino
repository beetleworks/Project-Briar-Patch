bool daytimeDecide (void) { //checks whether light sensor detects daytime or nighttime, returns a boolean
  int LDRval = analogRead(LDR_Pin);
  int daylightThreshold = 300;
  if (LDRval < daylightThreshold) {
    return true; //daytime
  } else {
    return false; //nighttime
  }
}

int eventDelayer (void) { //generates and returned length of delay period between events, in minutes
  int minuteTime = random(2, 4); //randomly chooses what minute to play event, between 3 and 18;
  //minuteTime = minuteTime*10; //elongates time of event delay
  minuteTime = 3;
  Serial.print("Minute Delay: ");
  Serial.println(minuteTime);
  return minuteTime;
}

bool delayChecker (void) { //uses rtc to check whether delay period has concluded
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