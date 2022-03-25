
Effect testEffect;

void effect_control_setup() {

  testEffect.create(0, continuousUse, true);
  testEffect.addWorkTime(19, 28, 01, 00);
}

void effect_control_loop() {

  timeClient.update();

  if ( testEffect.isTime() ) {
    Serial.println("Test Efekt Çalışıyor.");
  }
}
