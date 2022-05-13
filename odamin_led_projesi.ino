#include "includes.h"

void setup() {
  Serial.begin(115200);
  delay(1000);
  
  effect_control_setup();
  blynk_setup();
  fastled_setup();
  startanimation();
  web_server_setup();
}
void loop() {
  
  blynk_loop();
  effect_control_loop();
  FastLED.show();
  
}
