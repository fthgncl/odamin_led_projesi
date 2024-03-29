#define ARRAY_SIZE(array) ((sizeof(array))/(sizeof(array[0])))
#include <AsyncJson.h>

#define buttonPIN D6

/* Blynk includes */
#define BLYNK_FIRMWARE_VERSION "0.1"
#define BLYNK_TEMPLATE_ID "TMPLixMwkJME"
#define BLYNK_DEVICE_NAME "Led Kontrol Cihazım"
#define BLYNK_AUTH_TOKEN "_cSSGCiFYwuC710XfSsZct2krnvqUR99"
#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
bool gameEffects = true;
/***********************/

/* Async WebServer includes */
#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <AsyncElegantOTA.h>
#define webServerPort 80
AsyncWebServer server(webServerPort);
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
#define MAX_AMPER 20
#define LED_DATA_PIN D7
#define LED_TYPE WS2812B
CRGB leds[NUM_LEDS];
/***********************/


/* Sound Sensor includes */
#include <FastLED.h>
#define SOUND_SENSOR_DATA_PIN D6
/***********************/

/* Prayer Times includes */
#include <ESP8266HTTPClient.h>
#define SAAT 0
#define DAKIKA 1
#define IMSAK 0
#define GUNES 1
#define OGLE 2
#define IKINDI 3
#define AKSAM 4
#define YATSI 5
int namazVakti[6][2];
/***********************/
