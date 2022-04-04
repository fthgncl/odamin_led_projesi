
void web_server_setup() {

  server.onNotFound(notFound);

  server.on("/gameevent", HTTP_POST,[](AsyncWebServerRequest * request) {},  NULL,  [](AsyncWebServerRequest * request, uint8_t *data, size_t len, size_t index, size_t total) {
    stringToData(uintToString(data));
    request->send(200);
  });

  AsyncElegantOTA.begin(&server);
  server.begin();
  Serial.println("HTTP server started");

}
void web_server_loop() {

}

void notFound(AsyncWebServerRequest *request) {
  request->send(404, "application/json", "{\"message\":\"Not found\"}");
}

void handleTest(AsyncWebServerRequest *request) {
  Serial.println(request->arg("plain"));
  Serial.println(request->arg("body"));
  Serial.println(request->arg("json"));
  Serial.println(request->arg("application/json"));
  AsyncResponseStream *response = request->beginResponseStream("application/json");
  DynamicJsonDocument json(1024);
  json["status"] = "ok";
  json["ssid"] = WiFi.SSID();
  json["ip"] = WiFi.localIP().toString();
  serializeJson(json, *response);
  request->send(response);
}
void analyzePost(AsyncWebServerRequest * request) {

  if (!gameEffects) {
    request->send(200, "text/plain", "Game effects are not active on the server");
    return;
  }

  StaticJsonDocument<100> data;
  if (request->hasParam("message"))
  {
    data["message"] = request->getParam("message")->value();
  }
  else {
    data["message"] = "No message parameter";
  }
  String response;
  serializeJson(data, response);
  request->send(200, "application/json", response);

  if (request->hasArg("plain") == false) {
    request->send(200, "text/plain", "you did not send any data");
    return;
  }

  request->send(200, "text/plain", "process completed");
  stringToData(request->arg("plain"));
}

void stringToData(String strJson) {

  DynamicJsonDocument doc(1024);
  deserializeJson(doc, strJson);
  JsonObject obj = doc.as<JsonObject>();

  getEvent(int(obj["gameid"]), obj["event"]);
}
String uintToString(uint8_t *str){
    return String((char *)str);
}
