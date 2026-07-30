void rgbCandleEffect (void) {
  do {

  int rgbCandle[3];
  rgbCandle[0] = random(200, 256);
  rgbCandle[1] = random(40, 110);
  rgbCandle[2] = 0;

  // Inject a rare, sudden drop in brightness to simulate a gust of wind
  if (random(0, 100) > 95) {
    rgbCandle[0] = random(100, 150);
    rgbCandle[1] = random(15, 40);
  }

  // Write values to the PWM pins
  analogWrite(LED_R, rgbCandle[0]);
  analogWrite(LED_G, rgbCandle[1]);
  analogWrite(LED_B, rgbCandle[2]);
  } while (lightEffectSignal == true);
}