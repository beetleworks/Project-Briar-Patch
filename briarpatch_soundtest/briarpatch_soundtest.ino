#include "Arduino.h"
#include "DFRobotDFPlayerMini.h"
#include <SoftwareSerial.h>
SoftwareSerial softSerial(9,8);
#define FPSerial softSerial

#define BUSYPIN 2

DFRobotDFPlayerMini mp3Player;


void setup() {
  FPSerial.begin(9600);
  Serial.begin(9600);

  pinMode(BUSYPIN, INPUT);

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

  mp3Player.volume(20);
  mp3Player.play(4);
}


void loop() {

  Serial.println(digitalRead(BUSYPIN));
  delay(1000);
  /*
    Individual Volumes of Tracks
    i=2 0001 Day_Norm: 30
    i=3 0002 Night_Norm: 25
    i=4 0003 Splash_Mountain: 25
    i=5 0004 Snow_White: 30
    i=6 0005 Bayou_Banjo: 25
    i=7 0006 Haunted_Mansion: 22
    i=1 0007 Wish_Upon: 25
  */
}
