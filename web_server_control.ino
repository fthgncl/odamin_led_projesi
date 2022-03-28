void web_server_setup() {

  server.on("/", HTTP_POST, handle_OnConnect);
  server.onNotFound(handle_NotFound);

  server.begin();

}
void web_server_loop() {
  server.handleClient();
}


void handle_NotFound() {
  server.send(404, "text/plain", "Sayfa Bulunamadı");
}

void handle_OnConnect() {

  if (server.hasArg("plain") == false) {
    server.send(200, "text/plain", "you did not send any data");
    return;
  }

  server.send(200, "text/plain", "process completed");
  stringToData(server.arg("plain"));
}

void stringToData(String strJson) {

  DynamicJsonDocument doc(1024);
  deserializeJson(doc, strJson);
  JsonObject obj = doc.as<JsonObject>();

  getEvent(int(obj["gameid"]), int(obj["effect"]));
}
