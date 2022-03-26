void startanimation() {
  for ( int j = 0 ; j < 6 ; j++ ) {
    for ( int i = 0 ; i < NUM_LEDS ; i++) {
      leds[i] = CRGB( j==0?20:0,j==2?20:0,j==4?20: 0);
    }
    delay(500);
    FastLED.show();
  }
  delay(500);
}
