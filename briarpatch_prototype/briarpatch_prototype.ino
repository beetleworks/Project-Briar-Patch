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

int currentState;

void setup() {
  pinMode(LDR_Pin, INPUT);
  pinMode(LED_R, OUTPUT);
  pinMode(LED_G, OUTPUT);
  pinMode(LED_B, OUTPUT);
  rgbColorSet(0,0,0);

  Serial.begin(9600);
  isDaytime = daytimeDecide();
  if (isDaytime == true) {
    currentState = 2;
  } else {
    currentState = 1;
  }

  URTCLIB_WIRE.begin();
  //rtc.set(30, 29, 17, 3, 28, 7, 26);
}

void loop() {
  int startTime[2];
  int currentTime[2];
  int eventDelay;
  int eventChoice;
  bool delayConfirm;
  do {
    rtc.refresh();
    if (currentState == 2) {
      startTime[0] = rtc.hour();
      startTime[1] = rtc.minute();
      eventDelay = eventDelayer();
      eventChoice = eventDecider();
      currentState = 1;
    }

    currentTime[0] = rtc.hour();
    currentTime[1] = rtc.minute();
    delayConfirm = delayChecker(startTime, currentTime, eventDelay);
    if (delayConfirm == true) {
      piratesBuzzer();
      startTime[0] = rtc.hour();
      startTime[1] = rtc.minute();
      eventDelay = eventDelayer();
      eventChoice = eventDecider();
    }
    
    rgbColorSet(236, 151, 247);
    isDaytime = daytimeDecide();
  } while (isDaytime == true);

  do {
      rtc.refresh();
    if (currentState == 1) {
      startTime[0] = rtc.hour();
      startTime[1] = rtc.minute();
      eventDelay = eventDelayer();
      eventChoice = eventDecider();
      currentState = 2;
    }

    currentTime[0] = rtc.hour();
    currentTime[1] = rtc.minute();
    delayConfirm = delayChecker(startTime, currentTime, eventDelay);
    if (delayConfirm == true) {
      lionBuzzer();
      startTime[0] = rtc.hour();
      startTime[1] = rtc.minute();
      eventDelay = eventDelayer();
      eventChoice = eventDecider();
    }
    
    rgbColorSet(255, 87, 0);
    isDaytime = daytimeDecide();
  } while (isDaytime == false);
}
