#ifndef EffectManager
#define EffectManager

#define MAX_EFFECT_COUNTS 10

const bool singleUse = true;
const bool continuousUse = !singleUse;
bool runByTime = true;

class Effect
{
  public:

    bool enable = false;
    bool useType; // true : single use , false continuous use
    int id = -1;
    bool manualWork;
    float startTime = -1.0;
    float endTime = -1.0;
    void (* setupFunction)(byte layer);
    void (* loopFunction)();
    int blynkVirtualPIN;

    void build(byte useType, void (* EFF_setupFunctioncs)(byte layer) , void (* EFF_loopFunction)(), int EFF_blynkVirtualPIN, int emptyLayer , float startTime = -1.0, float endTime = -1.0, bool manualWork = false) {
      this->enable = true;
      this->id = emptyLayer;
      this->useType = useType;
      this->manualWork = manualWork;
      this->setupFunction = EFF_setupFunctioncs;
      this->loopFunction = EFF_loopFunction;
      this->blynkVirtualPIN = EFF_blynkVirtualPIN;

      if ( startTime != -1.0 || endTime != -1.0 ) {
        this->startTime = startTime;
        this->endTime = endTime;
      }

    }

    bool isTime() {

      float nowTime = timeClient.getHours() + (timeClient.getMinutes() / 60.0);

      if ( startTime > endTime ) {
        if ( nowTime <= endTime || nowTime >= startTime )
          return true;
      }
      else
      {
        if ( startTime <= nowTime && nowTime <= endTime )
          return true;
      }

      return false;
    }
};
Effect allEffects[MAX_EFFECT_COUNTS];
int findEmptyLayer() {
  for ( byte i = 0 ; i < MAX_EFFECT_COUNTS ; i++ )
    if ( allEffects[i].id == -1 )
      return i;

  return -1;
}
float calculateTime(byte Hour , byte Minute) {
  return (Hour + (Minute / 60.0));
}
void CreateEffect(byte useType, void (* setupFunction)(byte layer) , void (* loopFunction)(), int blynkVirtualPIN, byte startHour = 0, byte startMinute = 0 , byte endHour = 0 , byte endMinute = 0) {
  int layer = findEmptyLayer();
  if ( layer == -1 )
    Serial.println("Eklenmeye çalışan efekt için boş katman bulunamadı.");
  else
    allEffects[layer].build(useType, setupFunction, loopFunction, blynkVirtualPIN, layer , calculateTime(startHour, startMinute), calculateTime(endHour, endMinute));

}
void changeEffectTimes(byte effectLayer , byte startHour = 0, byte startMinute = 0 , byte endHour = 0 , byte endMinute = 0 ) {
  allEffects[effectLayer].build(allEffects[effectLayer].useType, allEffects[effectLayer].setupFunction , allEffects[effectLayer].loopFunction, allEffects[effectLayer].blynkVirtualPIN, allEffects[effectLayer].id, calculateTime(startHour, startMinute), calculateTime(endHour, endMinute), allEffects[effectLayer].manualWork);
}
int findEffectIDLayerVirtualPin(int blynkVirtualPIN) {
  for ( byte i = 0 ; i < MAX_EFFECT_COUNTS ; i++ )
    if ( allEffects[i].id != -1 )
      if (allEffects[i].blynkVirtualPIN == blynkVirtualPIN)
        return i;

  return -1;
}
void deleteLayer(byte layer) {
  if ( layer < MAX_EFFECT_COUNTS )
    allEffects[layer].id = -1;
}
#endif
