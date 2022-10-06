int flashingStarsPeriot;
void flashingStars_setup(byte effectID) {

}
void flashingStars_loop() {
  flashingStarsPeriot++;
  if ( flashingStarsPeriot % 5 != 0 )
    return;
    
  flashingStarsPeriot = 0;
  
  fadeToBlackBy( leds, 232, 10);
  int pos = random16(232);
  leds[pos] += CHSV( random8(128), random8(128), random8(128));
}
