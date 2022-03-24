/* Blynk includes */
#define BLYNK_TEMPLATE_ID "TMPLixMwkJME"
#define BLYNK_DEVICE_NAME "Led Kontrol Cihazım"
#define BLYNK_AUTH_TOKEN "_cSSGCiFYwuC710XfSsZct2krnvqUR99"
#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
/***********************/

char ssid[] = "TRC";
char pass[] = "ist34ank06";

void blynk_setup() {
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
}
void blynk_loop() {
  Blynk.run();
}
