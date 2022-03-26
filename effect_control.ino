#define EFFECT_COUNTS 5

Effect allEffects[EFFECT_COUNTS];
bool firtTimeEffect[EFFECT_COUNTS];

Effect EF_reel00;

void effect_control_setup() {

  EF_reel00.create(continuousUse);
  allEffects[0] = EF_reel00;
  EF_reel00.addWorkTime(12, 06, 12, 06);

}
void effect_control_loop() {

  timeClient.update();

  for ( byte i = 0 ; i < effectCount; i++ ) {
    bool runTime = allEffects[i].isTime();
    if ( runTime ) {
      if ( firstTimeEffectControl(i, runTime)) {
        Serial.print(i);
        Serial.println(" -> ilk defa çalıştı.");
      }
      else
        runEffect(i);
    }
  }
  delay(2000);
}
void runEffect(byte num) {
  switch (allEffects[num].id) {
        case EF_reel00.id: ReelEfect();
          break;

bool firstTimeEffectControl(byte i, bool runTime) {

  if ( firtTimeEffect[i] != runTime ) {
    firtTimeEffect[i] = runTime;
    return true;
  }

  return false;
}
