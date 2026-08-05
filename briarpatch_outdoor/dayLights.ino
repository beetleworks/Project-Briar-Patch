void dayLightsNorm (void) {
      int brightness = beatsin8(12, 10, 255);
      fill_solid(leds, NUM_LEDS, CRGB(80, 162, 240));
      FastLED.setBrightness(brightness);
      FastLED.show();
}

void splashEffect (void) {}

void swEffect (void) {}