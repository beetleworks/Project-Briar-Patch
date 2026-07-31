//DOESNT PLAY SECOND EASTER EGG

#define LDR_Pin A1
#define BUSYPIN 2

#include "Arduino.h"
#include "DFRobotDFPlayerMini.h"
#include <uRTCLib.h>
#include <SoftwareSerial.h>
SoftwareSerial softSerial(9,8);
#define FPSerial softSerial

DFRobotDFPlayerMini mp3Player;

uRTCLib rtc(0x68);

bool remainsDaytime; //true when daytime, false when nighttime, used to signal when state changes
uint8_t startTime[2];
uint8_t eventDelay;

bool eventPlayed;
bool eventConfirm;

void setup() {
  pinMode(LDR_Pin, INPUT);
  pinMode(BUSYPIN, INPUT);

  randomSeed(analogRead(A0));

  if (daytimeDecide() == true) {
    remainsDaytime = false;
  } else {
    remainsDaytime = true;
  }

  FPSerial.begin(9600);
  Serial.begin(9600);
  URTCLIB_WIRE.begin();
  //rtc.set(30, 29, 17, 3, 28, 7, 26);

  Serial.println();
  Serial.println(F("DFRobot DFPlayer Mini Demo"));
  Serial.println(F("Initializing DFPlayer ... (May take 3~5 seconds)"));
  if (!mp3Player.begin(FPSerial, /*isACK = */true, /*doReset = */true)) {  //Use serial to communicate with mp3.
    Serial.println(F("Unable to begin:"));
    Serial.println(F("1.Please recheck the connection!"));
    Serial.println(F("2.Please insert the SD card!"));
    while(true);
  }
  Serial.println(F("DFPlayer Mini online."));
  mp3Player.setTimeOut(500); //Set serial communictaion time out 500ms
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
      mp3Player.pause();
      mp3Player.volume(20);
      mp3Player.loop(2);
    }

    eventConfirm = delayChecker();
    if (eventConfirm == true) {
      if (eventPlayed == false) {
        eventPlayer();
      }
      eventPlayed = false;
      eventConfirm = delayChecker();
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
      mp3Player.pause();
      mp3Player.volume(25);
      mp3Player.loop(3);
    }

    
    eventConfirm = delayChecker();
    if (eventConfirm == true) {
      if (eventPlayed == false) {
        eventPlayer();
      }
      eventPlayed = false;
      eventConfirm = delayChecker();
    }
    
  } while (daytimeDecide() == false);


}