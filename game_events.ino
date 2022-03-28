CRGB ledsCopy[NUM_LEDS];

void valorantEffect(int effectNo){
  gameEffectStarted();
  
  leds[100].setRGB(255,0,0);
  FastLED.show();
  
  delay(1000);
  
  gameEffectStoped();
}

void gameEffectStartProtocol(){
  memcpy(ledsCopy, leds, sizeof(leds));
  FastLED.clear();
}
void gameEffectStopedProtocol(){
  memcpy(leds, ledsCopy, sizeof(leds));
}
