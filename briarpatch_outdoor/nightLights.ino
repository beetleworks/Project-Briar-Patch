void bbEffect (void) {
      int brightness = beatsin8(6, 10, 255);
      fill_solid(leds, NUM_LEDS, CRGB( 204, 85, 0));
      FastLED.setBrightness(brightness);
      FastLED.show();
}

void hmEffect (void) {
  //this function is a green/purple breathing
  //green is R 0, G 255, B 62
  //purple is R 214, G 0, B 255

  CRGB hmGreen = CRGB(0, 255, 562);
  CRGB hmPurple = CRGB(214, 0, 255);

  int hmWave = beatsin8(12, 10, 255);

  CRGB hmBlend = nblend(hmGreen, hmPurple, (fract8)hmWave);
  fill_solid(leds, NUM_LEDS, hmBlend);
  FastLED.show();
}

void wishEffect (bool inputYN) {
  //this function is a blue/light yellow chaser with 6 segments (24 leds each)
  //blue is R 110, G 161, B 235
  //yellow is R 255, G 254, B 191
}