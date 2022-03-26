void fastled_setup(){
  FastLED.addLeds<LED_TYPE, DATA_PIN, GRB>(leds, NUM_LEDS);
  delay(1000);
  clearLeds();
}
void clearLeds() {
  FastLED.clear();
  FastLED.show();//delay(10)
}
