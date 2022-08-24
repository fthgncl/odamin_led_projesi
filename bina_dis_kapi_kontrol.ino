void binaKapisiniAc() {
  WiFiClient client;
  HTTPClient http;
  http.begin(client, "192.168.1.199/kapiyiac");
}
