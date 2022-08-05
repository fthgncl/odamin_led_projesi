


void prayerTimesUpdate() {

  if ((WiFi.status() == WL_CONNECTED)) {
    WiFiClient client;
    HTTPClient http;

    http.begin(client, "http://namaz-vakti-api.herokuapp.com/data?region=9541");
    int httpCode = http.GET();

    if (httpCode > 0) {
      gununNamazVakitleriniCek(http.getString());
      Serial.println("Namaz vakitleri çekildi");
    }
    else 
    {
      Serial.println("Namaz vakiti sunucusuna gönderilen istekte hata oluştu.");
    }

    http.end();
  }
}
void gununNamazVakitleriniCek(String payload) {
  byte tirnakSayaci = 0;
  byte vakitNo = 0;
  bool saatBirimi = 0;
  bool ondalikBirimi = 0;
  char saat[2];
  char dakika[2];
  for ( int i = 0 ; tirnakSayaci < 14 ; i++ ) {
    delay(100);
    if ( payload[i] == '\"' ) {
      saatBirimi = 0;
      tirnakSayaci++;
      i++;
    }

    if ( payload[i] == ':' ) {
      saatBirimi = 1;
      i++;
    }

    if ( tirnakSayaci <= 2 )
      continue;

    if ( tirnakSayaci % 2 == 1 ) {

      if ( !saatBirimi ) { // Saat
        saat[ondalikBirimi] = payload[i];
      }
      else  // Dakika
      {
        dakika[ondalikBirimi] = payload[i];
      }
      ondalikBirimi = !ondalikBirimi;
    }
    else
    {
      saatBirimi = !saatBirimi;

      namazVakti[vakitNo][0] = (saat[0] - '0') * 10;
      namazVakti[vakitNo][0] += saat[1] - '0';

      namazVakti[vakitNo][1] = (dakika[0] - '0') * 10;
      namazVakti[vakitNo][1] += dakika[1] - '0';

      vakitNo++;
    }
  }
}
