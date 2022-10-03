void prayerTimesUpdate() {

  if ((WiFi.status() == WL_CONNECTED)) {
    WiFiClient client;
    HTTPClient http;

    http.begin(client, "http://ezanvakti.herokuapp.com/vakitler/9541");
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
void gununNamazVakitleriniCek(String data) {
  koseliParantezKaldir(data);
  ilkJsonTaniminiBul(data);

  DynamicJsonDocument doc(2048);
  deserializeJson(doc, data);
  JsonObject JSONnamazVakti = doc.as<JsonObject>();
  String vakitler[6] = {"Imsak","Gunes","Ogle","Ikindi","Aksam","Yatsi"};
  for ( byte i = 0 ; i < 6 ; i ++ ) {
    
    String stringVakit = JSONnamazVakti[vakitler[i]].as<String>();
    byte ayrac = stringVakit.indexOf(":");
    namazVakti[i][0] = stringVakit.substring(0, ayrac).toInt();
    namazVakti[i][1] = stringVakit.substring(ayrac + 1, stringVakit.length()).toInt();

  }
}
void ilkJsonTaniminiBul(String & data) {

  int baslangic = data.indexOf("{");
  int bitis = data.indexOf("},{");
  if ( bitis == -1 )
    bitis = data.indexOf("}");

  bitis++;
  data = data.substring(baslangic, bitis);
}
String koseliParantezKaldir(String data) {
  int baslangic = data.indexOf("[");
  int bitis = data.lastIndexOf("]");

  if ( baslangic != -1 && bitis != -1 )
    return data.substring(baslangic + 1, bitis);

  return data;
}
