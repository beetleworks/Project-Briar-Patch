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
  CRGB hmGreen = CRGB(0, 255, 62);
  CRGB hmPurple = CRGB(214, 0, 255);
  int hmWave = beatsin8(8, 10, 255);
  CRGB hmBlend = nblend(hmGreen, hmPurple, (fract8)hmWave);
  fill_solid(leds, NUM_LEDS, hmBlend);
  FastLED.setBrightness(200);
  FastLED.show();
}

void wishEffect (void) {
  //this function is a yellow shooting star effect
  //yellow is R 255, G 254, B 191
  
  int fadeRate = 30;
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i].fadeToBlackBy(fadeRate);
  }

  leds[wish_pos] = CRGB(255, 254, 191);

  FastLED.show();
  delay(20);

  wish_pos++;
  if (wish_pos >= NUM_LEDS) {
    wish_pos = 0;
  }
}