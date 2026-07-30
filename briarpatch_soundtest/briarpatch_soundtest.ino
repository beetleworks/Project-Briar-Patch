#include "Arduino.h"
#include "DFRobotDFPlayerMini.h"
#define FPSerial Serial1


DFRobotDFPlayerMini mp3Player;


void setup() {
  FPSerial.begin(9600);
  Serial.begin(9600);

  mp3Player.volume(15);
  mp3Player.play(1);
}


void loop() {
  /*
    Individual Volumes of Tracks
    0001 Day_Norm:
    0002 Night_Norm:
    0003 Splash_Mountain:
    0004 Snow_White:
    0005 Bayou_Banjo:
    0006 Haunted_Mansion:
    0007 Wish_Upon:
  */
}
