char ssid[] = "TRC";
char pass[] = "ist34ank06";

void blynk_setup() {
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
}
void blynk_loop() {
  Blynk.run();
}
