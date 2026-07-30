void songOne(void) {
  Serial.println("Song One");
  tone(BUZZER, 200);
  delay(3000);
  noTone(BUZZER);
}

void songTwo(void) {
  Serial.println("Song Two");
  tone(BUZZER, 200);
  delay(1000);
  noTone(BUZZER);
  delay(1000);
  tone(BUZZER, 200);
  delay(1000);
  noTone(BUZZER);
}