#include "includes.h"

void setup() {
  Serial.begin(115200);
  delay(1000);

  blynk_setup();
  prayerTimesUpdate();
  effect_control_setup();
  fastled_setup();
  startanimation();
  web_server_setup();
}
void loop() {

  blynk_loop();
  effect_control_loop();
  FastLED.show();

  EVERY_N_MILLISECONDS(50) {
    button_control();
  }

}
