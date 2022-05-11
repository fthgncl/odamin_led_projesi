char ssid[] = "TRC";
char pass[] = "ist34ank06";

#define PIN_RunByTime = 0
byte manualBlynkRGB[3];

void blynk_setup() {
  WiFi.mode(WIFI_STA);
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  printBlynkConsole("");
}
BLYNK_CONNECTED(){
  Serial.println("Blynk Connected Çalıştı...");
  blynkUpdateDashBoard();
  sendSystemReport();
}

void blynk_loop() {
  Blynk.run();
}

void sendSystemReport() {

  timeClient.update();
  Blynk.virtualWrite(V9, "Son Güncellenme Tarihi : " + getTimeStampString() + " | Local IP : " + WiFi.localIP().toString());
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
  Blynk.virtualWrite(V4, gameEffects);

  for ( byte i = 0 ; i < MAX_EFFECT_COUNTS ; i++ ) {
    if ( allEffects[i].id != -1 ) {
      Blynk.virtualWrite(allEffects[i].blynkVirtualPIN, allEffects[i].enable ? activityStatus(i) : false);
    }
  }
}
bool activityStatus(byte effectNo) {
  return runByTime ? getEffectIsTimeStatus(effectNo) : getEffectManualWorkStatus(effectNo);
}

BLYNK_WRITE(V0)  {  // Zamana Göre İşleyiş
  runByTime = param.asInt();
  blynkUpdateDashBoard();
}
BLYNK_WRITE_DEFAULT()
{
  int pin = request.pin;
  int value = param.asInt();
  for ( byte i = 0 ; i < MAX_EFFECT_COUNTS ; i++ ) {
    if ( allEffects[i].blynkVirtualPIN == pin ) {
      changeEffectManualWorkStatus(i, runByTime ? false : value);
      Blynk.virtualWrite(pin, activityStatus(i));
    }
  }
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

void printBlynkConsole(String message) {
  Blynk.virtualWrite(V11, message);
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
  Blynk.virtualWrite(allEffects[num].blynkVirtualPIN, idata);
}
