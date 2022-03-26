#define ARRAY_SIZE(array) ((sizeof(array))/(sizeof(array[0])))

/* Blynk includes */
#define BLYNK_TEMPLATE_ID "TMPLixMwkJME"
#define BLYNK_DEVICE_NAME "Led Kontrol Cihazım"
#define BLYNK_AUTH_TOKEN "_cSSGCiFYwuC710XfSsZct2krnvqUR99"
#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
/***********************/

/* NTP Client includes */
#include <NTPClient.h>
#include <WiFiUdp.h>
WiFiUDP ntpUDP;
const byte GMT = 3;
NTPClient timeClient(ntpUDP, "pool.ntp.org", 3600*GMT);
/***********************/

/* Effect Manager includes */
#include "EffectManager.h"


/* FastLED includes */
#include <FastLED.h>
#define NUM_LEDS 290
#define DATA_PIN D7
#define LED_TYPE WS2812B
CRGB leds[NUM_LEDS];
/***********************/