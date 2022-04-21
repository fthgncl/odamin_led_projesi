void fastled_setup(){
  FastLED.addLeds<LED_TYPE, DATA_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setMaxPowerInVoltsAndMilliamps(5,MAX_AMPER*1000);
  delay(1000);
  clearLeds();
}
void clearLeds() {
  FastLED.clear();
  FastLED.show();//delay(10)
}
