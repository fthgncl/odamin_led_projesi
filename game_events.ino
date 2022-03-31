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


void valorantEffect(int effectNo) {

  switch (effectNo) {
    case 1: deathEffect();
      break;
  }


}
void deathEffect() {
  changeAllLedsClorRed(0);
  delay(20);
  changeAllLedsClorRed(255);
  delay(20);
  changeAllLedsClorRed(0);
  delay(20);
  changeAllLedsClorRed(255);
  delay(20);
  changeAllLedsClorRed(0);
  delay(20);
  changeAllLedsClorRed(255);
  delay(20);
  changeAllLedsClorRed(0);
  delay(20);
  changeAllLedsClorRed(255);
  delay(20);
  changeAllLedsClorRed(0);
  delay(20);
  changeAllLedsClorRed(255);
  delay(20);
  changeAllLedsClorRed(0);
  delay(20);
  changeAllLedsClorRed(255);

  
  while ( leds[0].r > 5 ) {
    changeAllLedsClorRed(leds[0].r-5);
  }
}
void changeAllLedsClorRed(byte _red) {
  for ( int i = 0 ; i < NUM_LEDS ; i++ ) {
    leds[i].setRGB(_red, 0, 0);
  }
  
  FastLED.show();
}
