#define LDR_Pin A1
#define BUSYPIN A3
#define LED_PIN 7

#include "Arduino.h"
#include "DFRobotDFPlayerMini.h"
#include <uRTCLib.h>
#include <SoftwareSerial.h>
#include <FastLED.h>

SoftwareSerial softSerial(9,8);
#define FPSerial softSerial

//LED Vars
#define NUM_LEDS 144
#define COLOR_ORDER GRB
#define CHIPSET WS2812B
CRGB leds[NUM_LEDS];
CRGBPalette16 currentPalette;

DFRobotDFPlayerMini mp3Player;

uRTCLib rtc(0x68);

bool isDaytime;
bool remainsDaytime; //true when daytime, false when nighttime, used to signal when state changes
uint8_t startTime[2];
uint8_t eventDelay;
bool eventPlayed = false;
bool eventDone = false;
bool eventConfirm;

//global vars for light effects
uint8_t gHue = 0;
int wish_pos = 0;



void setup() {
  delay(3000);
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
  //rtc.set(30, 53, 9, 6, 31, 7, 26);
  rtc.refresh();
  startTime[0] = rtc.hour();
  startTime[1] = rtc.minute();
  Serial.println();
  eventDelay = eventDelayer();

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

  FastLED.addLeds<CHIPSET, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
  

  nightEffect(false);
  hmEffect();
}

void loop() {
  while (isDaytime == true) { //daytime Loop
    if (eventConfirm == false) {
      if (remainsDaytime == false) {
        Serial.println("Daytime Detected");
        startTime[0] = rtc.hour();
        startTime[1] = rtc.minute();
        eventDelay = eventDelayer();
        remainsDaytime = true;
        dayEffect();
        Serial.println("Daytime Setup");
      }

      dayLightsNorm();

      eventConfirm = delayChecker();
      isDaytime = daytimeDecide();
      //Serial.print("Event Confirm: ");
      //Serial.println(eventConfirm);

    } else if (eventConfirm == true) {

      if (eventPlayed == false) {
        eventPlayer();
      } else if (eventPlayed == true && eventDone == true) {
        eventConfirm = delayChecker();
        eventPlayed = false;
        eventDone = false;
      }
      }
    }



  while (isDaytime == false) { //nighttime loop
    if (eventConfirm == false) {
      if (remainsDaytime == true) {
        Serial.println("Nighttime Detected");
        startTime[0] = rtc.hour();
        startTime[1] = rtc.minute();
        eventDelay = eventDelayer();
        remainsDaytime = false;
        nightEffect(true);
        Serial.println("Nighttime Setup");
      }

      normFire2012(true);

      eventConfirm = delayChecker();
      isDaytime = daytimeDecide();
      //Serial.print("Event Confirm: ");
      //Serial.println(eventConfirm);

    } else if (eventConfirm == true) {

      if (eventPlayed == false) {
        eventPlayer();
      } else if (eventPlayed == true && eventDone == true) {
        eventConfirm = delayChecker();
        eventPlayed = false;
        eventDone = false;
      }
    }
  }


}