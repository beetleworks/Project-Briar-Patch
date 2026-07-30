#define LDR_Pin A1

#include "Arduino.h"
#include "DFRobotDFPlayerMini.h"
#include <uRTCLib.h>
#define FPSerial Serial1

DFRobotDFPlayerMini mp3Player;

uRTCLib rtc(0x68);

bool remainsDaytime; //true when daytime, false when nighttime, used to signal when state changes
uint8_t startTime[2];
uint8_t eventDelay;

void setup() {
  pinMode(LDR_Pin, INPUT);

  randomSeed(analogRead(A0));

  isDaytime = daytimeDecide();
  if (isDaytime == true) {
    remainsDaytime = false;
  } else {
    remainsDaytime = true;
  }

  FPSerial.begin(9600);
  Serial.begin(9600);
  URTCLIB_WIRE.begin();
  //rtc.set(30, 29, 17, 3, 28, 7, 26);

  mp3Player.volume(15);
}

void loop() {

  do { //daytime Loop
    rtc.refresh();
    if (remainsDaytime == false) {
      Serial.println("Daytime Detected");
      startTime[0] = rtc.hour();
      startTime[1] = rtc.minute();
      eventDelay = eventDelayer();
      remainsDaytime = true;
      mp3Player.loop(1);
    }

    if (delayChecker() == true) {
      eventPlayer();
    }
    
  } while (daytimeDecide() == true);


  do { //nighttime loop
      rtc.refresh();
    if (remainsDaytime == true) {
      Serial.println("Nighttime Detected");
      startTime[0] = rtc.hour();
      startTime[1] = rtc.minute();
      eventDelay = eventDelayer();
      remainsDaytime = false;
      mp3Player.loop(2)
    }

    if (delayChecker() == true) {
      eventPlayer();
      startTime[0] = rtc.hour();
      startTime[1] = rtc.minute();
      eventDelay = eventDelayer();
      mp3Player.loop(2);
    }
    
  } while (daytimeDecide() == false);


}