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
  minuteTime = 1; //manual minute selection for troubleshooting
  Serial.print("Minute Delay: ");
  Serial.println(minuteTime);
  return minuteTime;
}

bool delayChecker (void) { //uses rtc to check whether delay period has concluded
  DateTime currT = rtc.now();
  TimeSpan minDifference;
  minDifference = currT - startTime;
  Serial.println(minDifference.minutes());

  if (minDifference.minutes() >= eventDelay) {
    return true;
  } else {
    return false;
  }
}