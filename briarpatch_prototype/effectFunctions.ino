void rgbColorSet (int redin, int greenin, int bluein) {
  analogWrite(LED_R, redin);
  analogWrite(LED_G, greenin);
  analogWrite(LED_B, bluein);
}

void eventPlayer (void) {
  int eventChoice = random(1,3);
  void (*buzzerSongList[])() = {
    piratesBuzzer, lionBuzzer
  };
  buzzerSongList[eventChoice]();

  rgbColorSet(random(0,256), random(0, 256), random(0,256));
}