void dayLightsNorm (void) {
      int brightness = beatsin8(12, 10, 255);
      fill_solid(leds, NUM_LEDS, CRGB(80, 162, 240));
      FastLED.setBrightness(brightness);
      FastLED.show();
}

void splashEffect (void) {
  // Fade all existing LEDs slightly to create a trail effect
  fadeToBlackBy(leds, NUM_LEDS, 20);

  // Calculate a moving position back and forth across the strip
  // beatsin16(BPM, lowest_index, highest_index)
  int pos = beatsin16(30, 0, NUM_LEDS - 1);
  
  // Set the pixel at the calculated position to the current hue color
  leds[pos] += CHSV(gHue, 255, 192);

  FastLED.show();
  
  // Slowly cycle the base color hue over time
  gHue++; 
}


void swEffect (void) {}