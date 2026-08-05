void dayLightsNorm (void) {
      int brightness = beatsin8(12, 10, 255);
      fill_solid(leds, NUM_LEDS, CRGB(80, 162, 240));
      FastLED.setBrightness(brightness);
      FastLED.show();
}

void splashEffect (void) {
  //this is a teal sweep function
  //the teal is R 0, G 242, B 255
  CRGB splashTeal = CRGB(0, 242, 255);
  FastLED.setBrightness(255);
  for (int i = 0; i <= NUM_LEDS; i++) {
    FastLED.clear();
    // Fill from index 0 up to current step 'i'
    fill_solid(leds, i, splashTeal);
    FastLED.show();
}


void swEffect (void) {
  // Fade all existing pixels slightly on every frame
  fadeToBlackBy(leds, NUM_LEDS, 32); 

  // Randomly add new twinkles (adjust '50' for density, max 255)
  if (random8() < 50) {
    int pos = random16(NUM_LEDS);
    // Assign a random vibrant hue with full brightness
    leds[pos] = CRGB(146, 215, 255); 
  }

  FastLED.setBrightness(255);
  FastLED.show();
}