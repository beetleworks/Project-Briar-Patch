void rgbColorSet (int redin, int greenin, int bluein) {
  analogWrite(LED_R, redin);
  analogWrite(LED_G, greenin);
  analogWrite(LED_B, bluein);
}