void eventPlayer (void) {
  eventPlayed = true;
  mp3Player.disableLoop();
  Serial.println("Running Event");
  randomSeed(analogRead(A0));
  mp3Player.pause();
  mp3Player.volume(20);
  
  if (daytimeDecide() == true) {
    int eventChoice = random(4, 6);
    mp3Player.pause();
    mp3Player.play(eventChoice);
    Serial.println("Day Event Play");
  } else if (daytimeDecide() == false) {
    int eventChoice = random(0, 3);
    int nightChoice[3] = {6, 7, 1};
    mp3Player.pause();
    mp3Player.play(nightChoice[eventChoice]);
    Serial.println("Night Event Play");
  }
  
  
  
  //Insert lighting effect here

  delay(5000);
  int busyStatus;
  do {
    busyStatus = digitalRead(BUSYPIN);
    Serial.println(busyStatus);
    delay(1000);
  } while (busyStatus == 0);
  
  if (busyStatus == 1) {
    mp3Player.pause();
    Serial.println("Play Finished");
        Serial.println("End Effect");
        startTime[0] = rtc.hour();
        startTime[1] = rtc.minute();
        eventDelay = eventDelayer();
        if (daytimeDecide() == true) {
          //Normal daytime lighting effect here
          mp3Player.volume(30);
          mp3Player.loop(2);
          mp3Player.enableLoop();
          return;
        } else {
          //Normal nighttime lighting effect here
          mp3Player.volume(25);
          mp3Player.loop(3);
          mp3Player.enableLoop();
          return;
        }
  }
}
/*
  if (mp3Player.available()) { //Once effect sound is done playing
  
    switch (mp3Player.readType()) {
      case DFPlayerPlayFinished:
        Serial.println("Play Finished");
        Serial.println("End Effect");
        startTime[0] = rtc.hour();
        startTime[1] = rtc.minute();
        eventDelay = eventDelayer();
        eventPlayed = false;
        if (daytimeDecide() == true) {
          //Normal daytime lighting effect here
          mp3Player.volume(30);
          mp3Player.loop(2);
        } else {
          //Normal nighttime lighting effect here
          mp3Player.volume(25);
          mp3Player.loop(3);
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
        }
        break;
    }
  }
}

/*
    Individual Volumes of Tracks
    i=2 0001 Day_Norm: 37
    i=3 0002 Night_Norm: 25
    i=4 0003 Splash_Mountain: 20
    i=5 0004 Snow_White: 28
    i=6 0005 Bayou_Banjo: 25
    i=7 0006 Haunted_Mansion: 22
    i=1 0007 Wish_Upon: 25
  */