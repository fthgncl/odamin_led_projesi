


void web_server_setup() {

  AsyncCallbackJsonWebHandler* handler = new AsyncCallbackJsonWebHandler("/gameevent", [](AsyncWebServerRequest * request, JsonVariant & json) {
    if (!gameEffects) {
      request->send(200, "application/json", "{\"message\":\"Game effects are not active on the server\"}");
      return;
    }

    request->send(200, "application/json", "{\"message\":\"process completed\"}");
    JsonObject jsonObj = json.as<JsonObject>();
    getEvent(int(jsonObj["gameid"]), String(jsonObj["event"]));
    
  });

  server.addHandler(handler);
  server.onNotFound(notFound);

  AsyncElegantOTA.begin(&server);
  server.begin();
  Serial.println("HTTP server started");

}
void notFound(AsyncWebServerRequest *request) {
  request->send(404, "application/json", "{\"message\":\"Not found\"}");
}
