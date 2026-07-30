void rgbColorSet (int redin, int greenin, int bluein) {
  analogWrite(LED_R, redin);
  analogWrite(LED_G, greenin);
  analogWrite(LED_B, bluein);
}


void eventPlayer (void) {
  randomSeed(analogRead(A0));
  int eventChoice = random(0,2);
  void (*buzzerSongList[])() = {
    songOne, songTwo
  };
  lightEffectSignal = true;
  rgbCandleEffect();
  buzzerSongList[eventChoice]();
  Serial.println("End Effect");
  lightEffectSignal = false;

}