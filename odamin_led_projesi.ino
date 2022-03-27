#include "includes.h"

void setup() {
  Serial.begin(115200);
  delay(1000);
  
  blynk_setup();
  fastled_setup();
  startanimation();
  effect_control_setup();
  web_server_setup();
}
void loop() {
  
  blynk_loop();
  effect_control_loop();
  web_server_loop();
  FastLED.show();
  
}
