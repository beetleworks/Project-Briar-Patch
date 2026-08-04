void hmEffect (bool inputYN) {
  //this function is a green/purple breathing
  //green is R 0, G 255, B 62
  //purple is R 214, G 0, B 255
  while (inputYN == true) {
    int startMin = rtc.minute();
    int startSec = rtc.second();

    while (((rtc.minute() * 60) + rtc.second()) - (((startMin * 60) + startSec) >= 5) {
      int brightness = beatsin8(12, 10, 255);
      fill_solid(leds, NUM_LEDS, CRGB(0, 255, 62));
      FastLED.setBrightness(brightness);
      FastLED.show();
    }

    startMin = rtc.Minute();
    startSec = rtc.Second();

    while (((rtc.minute() * 60) + rtc.second()) - (((startMin * 60) + startSec) >= 5) {
      int brightness = beatsin8(12, 10, 255);
      fill_solid(leds, NUM_LEDS, CRGB(214, 0, 255));
      FastLED.setBrightness(brightness);
      FastLED.show();
    }
  }
}

void wishEffect (bool inputYN) {
  //this function is a blue/light yellow chaser with 6 segments (24 leds each)
  //blue is R 110, G 161, B 235
  //yellow is R 255, G 254, B 191
}