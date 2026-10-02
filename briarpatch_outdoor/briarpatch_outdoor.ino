#define LDR_Pin A1
#define LED_PIN 7

#include "Arduino.h"
#include "DFRobotDFPlayerMini.h"
#include "RTClib.h"
#include <SoftwareSerial.h>
#include <FastLED.h>

//DFPlayer Definitions
SoftwareSerial softSerial(8,9); //RX, TX ports for DFPlayerMini module
#define FPSerial softSerial
DFRobotDFPlayerMini mp3Player;

//LED Definitions
#define NUM_LEDS 144
#define COLOR_ORDER GRB
#define CHIPSET WS2812B
CRGB leds[NUM_LEDS];
CRGBPalette16 currentPalette;

//RTC Definitions
RTC_DS1307 rtc;

bool isDaytime; //true when daytime, false when nighttime, used to store info on daylight state
bool remainsDaytime; //true when daytime, false when nighttime, used to signal when state changes
DateTime startTime; //hour, minute array that signals the beginning of the norm (between events) period
int eventDelay; //delay between events, in minutes. Range can be set in timeFunctions tab
bool eventConfirm; //confirms that it's time to trigger event
bool eventPlayed = false; //confirms that event has started
bool eventDone = false; //confirms that event has ended
//NOTE: eventConfirm, eventPlayed, and eventDone are confusing so use this analogy. eventConfirm says Go! eventPlayed says Going! eventDone says Gone!

int wish_pos = 0; //global vars for wishEffect lighting effect



void setup() {
  delay(3000);
  pinMode(LDR_Pin, INPUT);

  randomSeed(analogRead(A0));

  if (daytimeDecide() == true) { //initially sets remainsDaytime
    remainsDaytime = false;
  } else {
    remainsDaytime = true;
  }

  FPSerial.begin(9600);
  Serial.begin(9600);
  if (!rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1);
  }
  rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  FastLED.addLeds<CHIPSET, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );

  Serial.println();
  Serial.println("_____________________________________________________");
  Serial.println("Initialize");
  Serial.println();

  startTime = rtc.now();
  eventDelay = eventDelayer();

  Serial.println();
  Serial.println(F("DFRobot DFPlayer Mini Demo"));
  Serial.println(F("Initializing DFPlayer ... (May take 3~5 seconds)"));
  delay(5000);
  if (!mp3Player.begin(FPSerial, /*isACK = */true, /*doReset = */true)) {  //Use serial to communicate with mp3.
    Serial.println(F("Unable to begin:"));
    Serial.println(F("1.Please recheck the connection!"));
    Serial.println(F("2.Please insert the SD card!"));
    while(true);
  }
  Serial.println(F("DFPlayer Mini online."));
  mp3Player.setTimeOut(500); //Set serial communictaion time out 500ms
  //nightEffect(false);
}

void loop() {
  while (isDaytime == true) { //daytime Loop
    if (eventConfirm == false) {
      if (remainsDaytime == false) { //runs only of state has swapped from night to day
        Serial.println("Daytime Detected");
        startTime = rtc.now();
        eventDelay = eventDelayer();
        remainsDaytime = true;
        dayEffect();
        Serial.println("Daytime Setup");
      }

      dayLightsNorm();

      eventConfirm = delayChecker(); //checks if it's time to trigger event
      isDaytime = daytimeDecide(); //check if it's still daytime

    } else if (eventConfirm == true) { //runs if it's daytime and time to trigger an event
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
      if (remainsDaytime == true) { //runs only if state has swapped from day to night
        Serial.println("Nighttime Detected");
        startTime = rtc.now();
        eventDelay = eventDelayer();
        remainsDaytime = false;
        nightEffect(true);
        Serial.println("Nighttime Setup");
      }

      normFire2012(true);

      eventConfirm = delayChecker();
      isDaytime = daytimeDecide(); //checks if it's still nighttime

    } else if (eventConfirm == true) { //runs if it's nighttime and time to trigger an event
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