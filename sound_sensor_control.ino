
int alkis = 0;
long algilama_araligi_baslangic = 0;
long algilama_araligi = 0;

void sound_sensor_setup() {
  pinMode(SOUND_SENSOR_DATA_PIN, INPUT);
}
void sound_sensor_loop() {

  if ( digitalRead(SOUND_SENSOR_DATA_PIN) == 0)
  {
    if (alkis == 0)
    {
      algilama_araligi_baslangic = algilama_araligi = millis();
      alkis++;
      //Serial.println("1. alkış");
    }
    else if (alkis > 0 && millis() - algilama_araligi >= 50)
    {
      algilama_araligi = millis();
      alkis++;
      //Serial.println("2. alkış");
    }
  }

  if (millis() - algilama_araligi_baslangic >= 400)
  {
    if (alkis == 2)
    {
      alkisYapildi();
    }
    alkis = 0;
  }
}
void alkisYapildi() {
  runByTime = !runByTime;
  blynkUpdateDashBoard();
}
