CRGB ledsCopy[NUM_LEDS];

void getEvent(int gameID , int effectNo ) {
  gameEffectStartProtocol();
  switch (gameID) {
    case 21640 : valorantEffect(effectNo);
      break;
  }
  gameEffectStopedProtocol();
}

void valorantEffect(int effectNo){
  gameEffectStartProtocol();
  
  leds[100].setRGB(255,0,0);
  FastLED.show();
  
  delay(1000);
  
  gameEffectStopedProtocol();
}

void gameEffectStartProtocol(){
  memcpy(ledsCopy, leds, sizeof(leds));
  FastLED.clear();
}
void gameEffectStopedProtocol(){
  memcpy(leds, ledsCopy, sizeof(leds));
}
