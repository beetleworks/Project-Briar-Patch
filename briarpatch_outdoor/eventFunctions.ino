void eventPlayer (void) {
  randomSeed(analogRead(A0));
  if (isDaytime == true) {
    int eventChoice = random(3, 5);
  } else {
    int eventChoice = random(5, 8);
  }
  mp3Player.pause();
  mp3Player.play(eventChoice);

  //Insert lighting effect here

  if (mp3Player.available()) { //Once effect sound is done playing
    switch (mp3Player.readType()) {
      case DFPlayerPlayFinished:
        Serial.println("Play Finished");
        Serial.println("End Effect");
        startTime[0] = rtc.hour();
        startTime[1] = rtc.minute();
        eventDelay = eventDelayer();
        if (daytimeDecide() == true) {
          //Normal daytime lighting effect here
          mp3Player.loop(1);
        } else {
          //Normal nighttime lighting effect here
          mp3Player.loop(2);
        }
        break;
      case DFPlayerError:
        Serial.print(F("DFPlayerError:"));
        switch (mp3Player.read()) {
          case Busy:
            Serial.println(F("Card not found"));
            break;
          case Sleeping:
            Serial.println(F("Sleeping"));
            break;
          case SerialWrongStack:
            Serial.println(F("Get Wrong Stack"));
            break;
          case CheckSumNotMatch:
            Serial.println(F("Check Sum Not Match"));
            break;
          case FileIndexOut:
            Serial.println(F("File Index Out of Bound"));
            break;
          case FileMismatch:
            Serial.println(F("Cannot Find File"));
            break;
        break;
    }
  }
}