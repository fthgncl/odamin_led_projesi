#define EFFECT_COUNTS 5

Effect allEffects[EFFECT_COUNTS];
bool firtTimeEffect[EFFECT_COUNTS];

void effect_control_setup() {

  allEffects[0].create(continuousUse);  /// DemoReel
  allEffects[0].addWorkTime(19, 00, 21, 00);

  allEffects[1].create(singleUse);  /// Circle night lamb
  allEffects[1].addWorkTime(04, 20, 06, 20);

  allEffects[2].create(continuousUse);  /// Flashing Stars
  allEffects[2].addWorkTime(21, 00, 00, 30);

  allEffects[3].create(continuousUse);  /// Dynamic Circle
  allEffects[3].addWorkTime(21, 00, 23, 30);

  allEffects[4].create(continuousUse);  /// Wandering Spots
  allEffects[4].addWorkTime(12, 00, 19, 00);

}
void effect_control_loop() {

  timeClient.update();
  
  bool runTime;
  for ( byte i = 0 ; i < EFFECT_COUNTS; i++ ) {
    if (allEffects[i].enable) {
      runTime = runByTime  ? allEffects[i].isTime()  : allEffects[i].manualWork;
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
      case 2 : flashingStars();
        break;
      case 3 : dynamic_circle_loop();
        break;
      case 4 : wandering_spots_setup();
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
      effectStopProtocol();
      
    updateBlinkEffectData(i, runByTime  ? allEffects[i].isTime()  : allEffects[i].manualWork );

  }
}
void effectStartProtocol(byte num) {
  runEffect(num, allEffects[num].useType);
}
void effectStopProtocol() {
  clearLeds();
  for ( byte i = 0 ; i < EFFECT_COUNTS ; i++ ) {
    if ( allEffects[i].id != -1 && (runByTime  ? allEffects[i].isTime()  : allEffects[i].manualWork) && allEffects[i].useType == singleUse )
      runEffect(i, singleUse);
  }
}

void changeEffectManualWorkStatus(byte num, bool manualWorkStatus) {
  allEffects[num].manualWork = manualWorkStatus;
}
bool getEffectManualWorkStatus(byte num) {
  return allEffects[num].manualWork;
}
bool getEffectIsTimeStatus(byte num) {
  return allEffects[num].isTime();
}
