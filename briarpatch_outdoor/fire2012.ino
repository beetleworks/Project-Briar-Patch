void normFire2012 (bool inputYN) {
  int framesPsec = 60;
  int COOLING = 50;
  int SPARKING = 120;

  if (inputYN == true) {
  // Array of temperature readings at each simulation cell
    static byte heat[NUM_LEDS];
  
    // Step 1.  Cool down every cell a little
      for( int i = 0; i < NUM_LEDS; i++) {
        heat[i] = qsub8( heat[i],  random8(0, ((COOLING * 10) / NUM_LEDS) + 2));
      }
    
      // Step 2.  Heat from each cell drifts 'up' and diffuses a little
      for( int k= NUM_LEDS - 3; k > 0; k--) {
        heat[k] = (heat[k - 1] + heat[k - 2] + heat[k - 2] ) / 3;
      }
      
      // Step 3.  Randomly ignite new 'sparks' of heat near the bottom
      if( random8() < SPARKING ) {
        int y = random8(7);
        heat[y] = qadd8( heat[y], random8(160,255) );
      }
  
      // Step 4.  Map from heat cells to LED colors
      for( int j = 0; j < NUM_LEDS; j++) {
          leds[j] = HeatMapping( heat[j]);
      }

    FastLED.setBrightness(200);
    FastLED.show();
    delay(1000/framesPsec);
  }
}





CRGB HeatMapping( uint8_t temperature) {
  CRGB heatcolor;
  
  uint8_t t192 = scale8_video( temperature, 192);
  uint8_t heatramp = t192 & 0x3F; // 0..63
  heatramp <<= 2; // scale up to 0..252
 
  if( t192 & 0x80) {
    // we're in the hottest third
    heatcolor.r = 255; // full red
    heatcolor.g = 255; // full green
    heatcolor.b = heatramp; // ramp up blue
  } else if( t192 & 0x40 ) {
    // we're in the middle third
    heatcolor.r = 255; // full red
    heatcolor.g = heatramp; // ramp up green
    heatcolor.b = 0; // no blue
  } else {
    // we're in the coolest third
    heatcolor.r = heatramp; // ramp up red
    heatcolor.g = 0; // no green
    heatcolor.b = 0; // no blue
  }
  
  return heatcolor;
}