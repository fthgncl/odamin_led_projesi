#include "includes.h"

void setup() {
  Serial.begin(115200);
  delay(1000);
  
  blynk_setup();
  effect_control_setup();
}
void loop() {
  
  blynk_loop();
  effect_control_loop();

  delay(100);
}
