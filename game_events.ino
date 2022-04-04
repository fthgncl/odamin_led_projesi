CRGB ledsCopy[NUM_LEDS];

void getEvent(int gameID , String event ) {
  gameEffectStartProtocol();
  switch (gameID) {
    case 21640 : valorantEffect(event);
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
