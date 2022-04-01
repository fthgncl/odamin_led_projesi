void wandering_spots_setup() {
  fadeToBlackBy( leds, NUM_LEDS, 10);
  uint8_t dothue = 0;
  for ( int i = 0; i < 3; i++) {
    leds[beatsin16( i + 7, 0, NUM_LEDS - 1 )] |= CHSV(dothue, 200, 255);
    dothue += 85;
  }
}
