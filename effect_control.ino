#define EFFECT_COUNTS 5

Effect allEffects[EFFECT_COUNTS];
bool firtTimeEffect[EFFECT_COUNTS];

void effect_control_setup() {

  allEffects[0].create(continuousUse);  /// DemoReel
  allEffects[0].addWorkTime(17, 52, 17, 52);

  allEffects[1].create(singleUse);  /// Avize Kemeri
  allEffects[1].addWorkTime(15, 00, 20, 00);

}
void effect_control_loop() {

  timeClient.update();

  for ( byte i = 0 ; i < effectCount; i++ ) {
    if (allEffects[i].enable) {
      bool runTime = allEffects[i].isTime();
      getEffectOnOFF(i, runTime);
      if ( runTime && allEffects[i].useType == continuousUse ) {
        runEffect(i, continuousUse);
      }
    }
  }
}
void runEffect(byte num, bool useType) {
  if ( useType == singleUse ) {       // Single Use
    switch ( allEffects[num].id ) {
      case 1 : avizeKemeri();
        break;
    }
  }
  else                              // Continuous Use
  {
    switch ( allEffects[num].id ) {
      case 0 : ReelEfect();
        break;
    }
  }
}
void getEffectOnOFF(byte i, bool runTime) {

  if ( firtTimeEffect[i] != runTime ) {
    firtTimeEffect[i] = runTime;

    if ( firtTimeEffect[i] )
      effectStartProtocol(i);
    else
      effectStopProtocol(i);

  }
}
void effectStartProtocol(byte num) {
  runEffect(num, allEffects[num].useType);
}
void effectStopProtocol(byte num) {
  clearLeds();
  for ( byte i = 0 ; i < EFFECT_COUNTS ; i++ )
    if ( allEffects[i].id != -1 && allEffects[i].isTime()&& allEffects[i].useType == singleUse )
      runEffect(i, singleUse);
}
