void eventPlayer (void) {
  eventPlayed = true;
  mp3Player.disableLoop();
  Serial.println("Running Event");
  
  if (daytimeDecide() == true) {
    eventChoice = random(4, 6);
    Serial.println("Day Event Play");
  } else if (daytimeDecide() == false) {
    nightEffect(false);
    int eventIndex = random(1, 4);
    Serial.print("Night event index: ");
    Serial.println(eventIndex);
    switch (eventIndex) {
      case 1:
      eventChoice = 6;
      break;
      case 2:
      eventChoice = 7;
      break;
      case 3:
      eventChoice = 1;
      break;
    }
    eventChoice = 7; // line is defaulting to chosen event for light effect testing
    Serial.print("Night Event Choice: ");
    Serial.println(eventChoice);
    Serial.println("Night Event Play");
  }

  switch (eventChoice) {
    case 4: //Splash Mountain
      mp3Player.pause();
      mp3Player.volume(18);
      mp3Player.play(eventChoice);
      Serial.println("Splash Mountain");
      break;
    case 5: //Snow White
      mp3Player.pause();
      mp3Player.volume(26);
      mp3Player.play(eventChoice);
      Serial.println("Snow White");
      break;
    case 6: //Bayou Banjo
      mp3Player.pause();
      mp3Player.volume(20);
      mp3Player.play(eventChoice);
      Serial.println("Bayou Banjo");
      break;
    case 7: //Haunted Mansion
      mp3Player.pause();
      mp3Player.volume(18);
      mp3Player.play(eventChoice);
      Serial.println("Haunted Mansion");
      break;
    case 1: //Wish Upon
      mp3Player.pause();
      mp3Player.volume(22);
      mp3Player.play(eventChoice);
      Serial.println("Wish Upon");
      break;
  }
  
  delay(1000);
  mp3Player.disableLoopAll();

  void (*lightEffects[7])() = {wishEffect, dayLightsNorm, normFire2012, splashEffect, swEffect, bbEffect, hmEffect};

  int busyStatus;
  busyStatus = analogRead(BUSYPIN);
  while (busyStatus < 500) {
    busyStatus = analogRead(BUSYPIN);
    lightEffects[eventChoice - 1]();
    Serial.println(busyStatus);
    delay(1000);
  }
  
  if (busyStatus >= 500) {
    mp3Player.pause();
    Serial.println("Play Finished");
        Serial.println("End Effect");
        rtc.refresh();
        startTime[0] = rtc.hour();
        startTime[1] = rtc.minute();
        eventDelay = eventDelayer();
        if (daytimeDecide() == true) {
          dayEffect();
          eventDone = true;
          return;
        } else {
          nightEffect(true);
          eventDone = true;
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
*/
void dayEffect (void) {
  mp3Player.pause();
  mp3Player.volume(28);
  mp3Player.enableLoop();
  mp3Player.loop(2);
  fill_solid(leds, NUM_LEDS, CRGB(0, 0, 0));
  FastLED.show();
  return;
}

void nightEffect (bool inputYN) {
  mp3Player.pause();
  mp3Player.volume(20);
  mp3Player.enableLoop();
  mp3Player.loop(3);
  //normFire2012(inputYN);
  return;
}

/*
    Individual Volumes of Tracks
    i=2 0001 Day_Norm: 27
    i=3 0002 Night_Norm: 22
    i=4 0003 Splash_Mountain: 18
    i=5 0004 Snow_White: 28
    i=6 0005 Bayou_Banjo: 25
    i=7 0006 Haunted_Mansion: 18
    i=1 0007 Wish_Upon: 25
  */