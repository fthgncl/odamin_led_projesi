char ssid[] = "TRC";
char pass[] = "ist34ank06";

#define PIN_RunByTime = 0
byte manualBlynkRGB[3];

void blynk_setup() {
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
}

void blynk_loop() {
  Blynk.run();
}

void blynkUpdateDashBoard() {
  Blynk.virtualWrite(V0, runByTime);
  Blynk.virtualWrite(V1, getEffectManualWorkStatus(0));
  Blynk.virtualWrite(V2, getEffectManualWorkStatus(1));
  Blynk.virtualWrite(V3, getEffectManualWorkStatus(2));
  Blynk.virtualWrite(V8, getEffectManualWorkStatus(3));
}

BLYNK_CONNECTED() {
  Blynk.syncAll();
  blynkUpdateDashBoard();
}

BLYNK_WRITE(V0)  {  // Zamana Göre İşleyiş
  runByTime = param.asInt();
  blynkUpdateDashBoard();
}

BLYNK_WRITE(V1)  {  // Efekt 1
  changeEffectManualWorkStatus(0, param.asInt());
}

BLYNK_WRITE(V2)  {  // Efekt 2
  changeEffectManualWorkStatus(1, param.asInt());
}

BLYNK_WRITE(V3)  {  // Efekt 3
  changeEffectManualWorkStatus(2, param.asInt());
}

BLYNK_WRITE(V8)  {  // Efekt 4
  changeEffectManualWorkStatus(3, param.asInt());
}

BLYNK_WRITE(V4)  {
  Serial.println("zxxxxxxxxxxxxxxxxxxxxxx");
}
BLYNK_WRITE(V5)  {
  manualBlynkRGB[0] = param.asInt();
  setManualRGB();
}
BLYNK_WRITE(V6)  {
  manualBlynkRGB[1] = param.asInt();
  setManualRGB();
}
BLYNK_WRITE(V7)  {
  manualBlynkRGB[2] = param.asInt();
  setManualRGB();
}


void setManualRGB() {
  if ( runByTime )
    return;

  for ( int i = 0; i < NUM_LEDS; i++) {
    leds[i].setRGB(manualBlynkRGB[0], manualBlynkRGB[1], manualBlynkRGB[2]);
  }
  
  if (manualBlynkRGB[0] + manualBlynkRGB[1] + manualBlynkRGB[2] == 0)
    effectStopProtocol();
}
