CRGB ledsCopy[NUM_LEDS];

void getEvent(int gameID , int effectNo ) {
  gameEffectStartProtocol();
  switch (gameID) {
    case 21640 : valorantEffect(effectNo);
      break;
  }
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


void valorantEffect(int effectNo) {

  switch (effectNo) {
    case 1: {
        for ( int i = 0 ; i < 100 ; i++) {
          addGlitter(80);
          FastLED.show();
          delay(10);
        }
      }
      break;
  }


}
