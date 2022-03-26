
void avizeKemeri() {
  byte color[3];
  color[0] = random(50);
  color[1] = random(50);
  color[2] = random(50);
  for ( int i = 289 ; i > 233 ; i --) {
    leds[i].setRGB(color[0], color[1], color[2]);
  }
  FastLED.show();
}
