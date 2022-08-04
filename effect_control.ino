unsigned long lastMoment = 0;
unsigned long nowMoment = 0;

bool firstTimeEffect[MAX_EFFECT_COUNTS];

void effect_control_setup() {

  CreateEffect(continuousUse, ReelEfect_setup, ReelEfect, V1, 19, 00, 21, 00); /// DemoReel
  CreateEffect(singleUse, avizeKemeri_setup, avizeKemeri_loop, V2, 04, 30, 05, 10); /// Circle night lamb
  CreateEffect(continuousUse, flashingStars_setup, flashingStars_loop, V3, 23, 00, 00, 00); /// Flashing Stars
  CreateEffect(continuousUse, dynamic_circle_setup, dynamic_circle_loop, V8, 23, 00, 23, 30); /// Dynamic Circle
  CreateEffect(continuousUse, wandering_spots_setup, wandering_spots_loop, V10, 16, 00, 19, 00); /// Wandering Spots
  CreateEffect(continuousUse, partly_cloudy_setup, partly_cloudy_loop, V12, 21, 00, 23, 00); /// Partly Cloudy
  //CreateEffect(continuousUse, random_moving_light_setup, random_moving_light_loop, V13, 23, 30, 00, 00); /// Random Moving Light

}
void effect_control_loop() {

  updateTime();
  bool runTime;
  for ( byte i = 0 ; i < MAX_EFFECT_COUNTS; i++ ) {
    if (allEffects[i].enable) {
      runTime = runByTime  ? allEffects[i].isTime()  : allEffects[i].manualWork;
      getEffectOnOFF(i, runTime);
      if ( runTime && allEffects[i].useType == continuousUse ) {
        allEffects[i].loopFunction();
      }
    }
  }
}
void updateTime() {
  nowMoment = millis();
  if ( nowMoment - lastMoment > 10000 ) {
    lastMoment = nowMoment;
    timeClient.update();
  }
}
void getEffectOnOFF(byte i, bool runTime) {

  if ( firstTimeEffect[i] != runTime ) {
    firstTimeEffect[i] = runTime;

    if ( firstTimeEffect[i] )
      effectStartProtocol(i);
    else
      effectStopProtocol();

    updateBlinkEffectData(i, runByTime  ? allEffects[i].isTime()  : allEffects[i].manualWork );

  }
}
void effectStartProtocol(byte id) {
  allEffects[id].setupFunction();
}
void effectStopProtocol() {
  clearLeds();
  for ( byte i = 0 ; i < MAX_EFFECT_COUNTS ; i++ ) {
    if ( allEffects[i].enable && (runByTime  ? allEffects[i].isTime()  : allEffects[i].manualWork) && allEffects[i].useType == singleUse )
      allEffects[i].setupFunction();
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
