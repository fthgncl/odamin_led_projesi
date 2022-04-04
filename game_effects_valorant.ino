void valorantEffect(String event) {
  if (event == "death") {
    valorant_deathEffect();
    return;
  }


}
void valorant_deathEffect() {
  for ( byte j = 0 ; j < 4 ; j++ ) {
    valorant_changeAllLedsClorRed(0);
    delay(random(30, 80));
    valorant_changeAllLedsClorRed(255);
    delay(random(30, 80));
  }
  delay(500);
  while ( leds[0].r >= 3 ) {
    valorant_changeAllLedsClorRed(leds[0].r - 3);
  }

}
void valorant_changeAllLedsClorRed(byte _red) {
  for ( int i = 0 ; i < NUM_LEDS ; i++ ) {
    leds[i].setRGB(_red, 0, 0);
  }
  FastLED.show();
}
