void web_server_setup() {

  server.on("/",HTTP_POST, handle_OnConnect);
  server.onNotFound(handle_NotFound);

  server.begin();
  
}
void web_server_loop() {
  server.handleClient();
}


void handle_NotFound() {
  server.send(404, "text/plain", "Sayfa Bulunamadı");
}

void handle_OnConnect() { //Handler for the body path

  if (server.hasArg("plain") == false) { //Check if body received

    server.send(200, "text/plain", "Body notxxx received");
    return;

  }

  String message = "Body received:\n";
  message += server.arg("plain");
  message += "\n";

  Serial.println(server.arg("plain"));

  server.send(200, "text/plain", message);
}
