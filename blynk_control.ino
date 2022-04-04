char ssid[] = "TRC";
char pass[] = "ist34ank06";

#define PIN_RunByTime = 0
byte manualBlynkRGB[3];

void blynk_setup() {
  WiFi.mode(WIFI_STA);
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
}

void blynk_loop() {
  Blynk.run();
}

void sendSystemReport() {

  timeClient.update();

  Blynk.virtualWrite(V9,"Son Güncellenme Tarihi : " + getTimeStampString() + " | Local IP : " + WiFi.localIP().toString() + " : " + String(webServerPort));


}
String getTimeStampString() {
  time_t rawtime = timeClient.getEpochTime();
  struct tm * ti;
  ti = localtime (&rawtime);

  uint16_t year = ti->tm_year + 1900;
  String yearStr = String(year);

  uint8_t month = ti->tm_mon + 1;
  String monthStr = month < 10 ? "0" + String(month) : String(month);

  uint8_t day = ti->tm_mday;
  String dayStr = day < 10 ? "0" + String(day) : String(day);

  uint8_t hours = ti->tm_hour;
  String hoursStr = hours < 10 ? "0" + String(hours) : String(hours);

  uint8_t minutes = ti->tm_min;
  String minuteStr = minutes < 10 ? "0" + String(minutes) : String(minutes);

  return yearStr + "/" + monthStr + "/" + dayStr + " " +
         hoursStr + ":" + minuteStr;
}
void blynkUpdateDashBoard() {
  Blynk.virtualWrite(V0, runByTime);
  Blynk.virtualWrite(V1, activityStatus(0));
  Blynk.virtualWrite(V2, activityStatus(1));
  Blynk.virtualWrite(V3, activityStatus(2));
  Blynk.virtualWrite(V8, activityStatus(3));
  Blynk.virtualWrite(V10, activityStatus(4));
  Blynk.virtualWrite(V4, gameEffects);
}
bool activityStatus(byte effectNo) {
  return runByTime ? getEffectIsTimeStatus(effectNo) : getEffectManualWorkStatus(effectNo);
}
BLYNK_CONNECTED() {
  blynkUpdateDashBoard();
  sendSystemReport();
}

BLYNK_WRITE(V0)  {  // Zamana Göre İşleyiş
  runByTime = param.asInt();
  blynkUpdateDashBoard();
}
BLYNK_WRITE(V1)  {  // Efekt 1
  changeEffectManualWorkStatus(0, runByTime ? false : param.asInt());
  Blynk.virtualWrite(V1, activityStatus(0));
}

BLYNK_WRITE(V2)  {  // Efekt 2
  changeEffectManualWorkStatus(1, runByTime ? false : param.asInt());
  Blynk.virtualWrite(V2, activityStatus(1));
  if ( getEffectManualWorkStatus(1) )
    runEffect(1, singleUse);
}

BLYNK_WRITE(V3)  {  // Efekt 3
  changeEffectManualWorkStatus(2, runByTime ? false : param.asInt());
  Blynk.virtualWrite(V3, activityStatus(2));
}

BLYNK_WRITE(V8)  {  // Efekt 4
  changeEffectManualWorkStatus(3, runByTime ? false : param.asInt());
  Blynk.virtualWrite(V8, activityStatus(3));
}
BLYNK_WRITE(V10)  {  // Efekt 5
  changeEffectManualWorkStatus(4, runByTime ? false : param.asInt());
  Blynk.virtualWrite(V10, activityStatus(4));
}
BLYNK_WRITE(V4)  {  // Game Effects ON/OFF
  gameEffects = param.asInt();
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
void updateBlinkEffectData(byte num, int idata) {
  switch (num) {
    case 0: Blynk.virtualWrite(V1, idata);
      break;

    case 1: Blynk.virtualWrite(V2, idata);
      break;

    case 2: Blynk.virtualWrite(V3, idata);
      break;

    case 3: Blynk.virtualWrite(V4, idata);
      break;

    case 4: Blynk.virtualWrite(V10, idata);
      break;
  }
}
