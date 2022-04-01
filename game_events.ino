CRGB ledsCopy[NUM_LEDS];

void getEvent(int gameID , int effectNo ) {
  gameEffectStartProtocol();
  switch (gameID) {
    case 21640 : valorantEffect(effectNo);
      break;
  }
  delay(2000);
  gameEffectStopedProtocol();
}

void gameEffectStartProtocol() {
  memcpy(ledsCopy, leds, sizeof(leds));
  FastLED.clear();
}

void gameEffectStopedProtocol() {
  memcpy(leds, ledsCopy, sizeof(leds));
  blynkUpdateDashBoard();
}
