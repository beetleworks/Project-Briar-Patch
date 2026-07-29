#define LDR_Pin A1
#define LED_R 3
#define LED_G 5
#define LED_B 6
#define BUZZER 8

#include <Arduino.h>
#include <pitches.h>
#include <uRTCLib.h>

bool isDaytime;
uRTCLib rtc(0x68);

bool remainsDaytime; //true when daytime, false when nighttime, used to signal when state changes
int startTime[2];
int eventDelay;

void setup() {
  pinMode(LDR_Pin, INPUT);
  pinMode(LED_R, OUTPUT);
  pinMode(LED_G, OUTPUT);
  pinMode(LED_B, OUTPUT);
  rgbColorSet(0,0,0);

  Serial.begin(9600);
  isDaytime = daytimeDecide();
  if (isDaytime == true) {
    remainsDaytime = false;
  } else {
    remainsDaytime = true;
  }

  URTCLIB_WIRE.begin();
  //rtc.set(30, 29, 17, 3, 28, 7, 26);
}

void loop() {

  do {
    rtc.refresh();
    if (remainsDaytime == false) {
      startTime[0] = rtc.hour();
      startTime[1] = rtc.minute();
      eventDelay = eventDelayer();
      remainsDaytime = true;
    }

    bool delayConfirm = delayChecker();
    if (delayConfirm == true) {
      eventPlayer();
      startTime[0] = rtc.hour();
      startTime[1] = rtc.minute();
      eventDelay = eventDelayer();
    }
    
    rgbColorSet(236, 151, 247);
    isDaytime = daytimeDecide();
  } while (isDaytime == true);


  do {
      rtc.refresh();
    if (remainsDaytime == true) {
      startTime[0] = rtc.hour();
      startTime[1] = rtc.minute();
      eventDelay = eventDelayer();
      remainsDaytime = false;
    }

    bool delayConfirm = delayChecker();
    if (delayConfirm == true) {
      eventPlayer();
      startTime[0] = rtc.hour();
      startTime[1] = rtc.minute();
      eventDelay = eventDelayer();
    }
    
    rgbColorSet(255, 87, 0);
    isDaytime = daytimeDecide();
  } while (isDaytime == false);


}
