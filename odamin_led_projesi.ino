#include "includes.h"

void setup() {
  Serial.begin(115200);
  delay(1000);
  
  blynk_setup();
  fastled_setup();
  startanimation();
  effect_control_setup();
  sound_sensor_setup();
  web_server_setup();
}
void loop() {
  
  blynk_loop();
  sound_sensor_loop();
  effect_control_loop();
  FastLED.show();
  
}
