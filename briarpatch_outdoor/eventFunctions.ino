void eventPlayer (void) {
  //stop current behavior
  eventPlayed = true;
  mp3Player.disableLoop();
  
  //choose which event to play
  int eventChoice; //simple indicator of wich event is chosen
  int trackLength; //arbitrary sign of length of audio track; manually set
  if (daytimeDecide() == true) {
    eventChoice = random(3, 5);
    Serial.println("Day Event Play");

  } else if (daytimeDecide() == false) {
    nightEffect(false);
    eventChoice = random(5, 8);
    Serial.println("Night Event Play");
  }

  //trigger event audio based on above choice
  eventChoice = 5; //manual event selection for troubleshooting
  switch (eventChoice) {
    //day events
    case 3: //Splash Mountain
      mp3Player.pause();
      mp3Player.volume(18);
      mp3Player.play(eventChoice);
      trackLength = 15;
      Serial.println("Splash Mountain");
      break;
    case 4: //Snow White
      mp3Player.pause();
      mp3Player.volume(24);
      mp3Player.play(eventChoice);
      trackLength = 109;
      Serial.println("Snow White");
      break;
    
    //night events
    case 5: //Bayou Banjo
      mp3Player.pause();
      mp3Player.volume(22);
      mp3Player.play(eventChoice);
      trackLength = 117;
      Serial.println("Bayou Banjo");
      break;
    case 6: //Haunted Mansion
      mp3Player.pause();
      mp3Player.volume(16);
      mp3Player.play(eventChoice);
      trackLength = 57;
      Serial.println("Haunted Mansion");
      break;
    case 7: //Wish Upon
      mp3Player.pause();
      mp3Player.volume(22);
      mp3Player.play(eventChoice);
      trackLength = 97;
      Serial.println("Wish Upon");
      break;
  }
  

  //mp3Player.disableLoopAll();
  void (*lightEffects[7])() = {dayLightsNorm, normFire2012, splashEffect, swEffect, bbEffect, hmEffect, wishEffect}; //puts all lighting effects into an array, so code below is more consolidated


  //plays lighting effects until iterator matches tracklength*10
  for (int i = 0; i <= ((trackLength)*10); i++) {
    lightEffects[eventChoice - 1]();
    Serial.println(i);
    delay(100);
  }

  //ends event and returns to normal behavior
  Serial.println("Loop Done");
  mp3Player.stop();
  delay(100);
  Serial.println("Play Finished");
      Serial.println("End Effect");
      startTime = rtc.now();
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



void dayEffect (void) {
  mp3Player.pause();
  mp3Player.volume(28);
  mp3Player.enableLoop();
  mp3Player.loop(1);
  fill_solid(leds, NUM_LEDS, CRGB(0, 0, 0));
  FastLED.show();
  return;
}



void nightEffect (bool inputYN) {
  mp3Player.pause();
  mp3Player.volume(18);
  mp3Player.enableLoop();
  mp3Player.loop(2);
  fill_solid(leds, NUM_LEDS, CRGB(0, 0, 0));
  FastLED.show();
  return;
}

/*
    Individual Volumes of Tracks
    i=1 0001 Day_Norm: 24
    i=2 0002 Night_Norm: 15
    i=3 0003 Splash_Mountain: 20
    i=4 0004 Snow_White: 26
    i=5 0005 Bayou_Banjo: 24
    i=6 0006 Haunted_Mansion: 18
    i=7 0007 Wish_Upon: 24
  */