#ifndef EffectManager
#define EffectManager

#define MAX_EFFECT_COUNTS 10

const bool singleUse = true;
const bool continuousUse = !singleUse;
int effectCount = 0;
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
    void (* setupFunction)();
    void (* loopFunction)();
    int blynkVirtualPIN;

    void build(byte useType, void (* EFF_setupFunctioncs)() , void (* EFF_loopFunction)(), int EFF_blynkVirtualPIN, byte startHour = 0, byte startMinute = 0 , byte endHour = 0 , byte endMinute = 0 , int id = effectCount) {
      this->enable = true;
      this->id = id;
      this->useType = useType;
      this->manualWork = false;
      this->setupFunction = EFF_setupFunctioncs;
      this->loopFunction = EFF_loopFunction;
      this->blynkVirtualPIN = EFF_blynkVirtualPIN;

      if ( startHour != 0 || startMinute != 0 || endHour != 0 || endMinute != 0 ) {
        startTime = startHour + (startMinute / 60.0);
        endTime = endHour + (endMinute / 60.0);
      }

      effectCount++;
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
Effect CreateEffect(byte useType, void (* setupFunction)() , void (* loopFunction)(), int blynkVirtualPIN, byte startHour = 0, byte startMinute = 0 , byte endHour = 0 , byte endMinute = 0) {
  allEffects[effectCount].build(useType, setupFunction, loopFunction, blynkVirtualPIN, startHour, startMinute, endHour, endMinute);
  return allEffects[effectCount - 1];
}
void changeEffectTimes(byte effectLayer , byte startHour = 0, byte startMinute = 0 , byte endHour = 0 , byte endMinute = 0 ) {
  allEffects[effectLayer].build(allEffects[effectLayer].useType, allEffects[effectLayer].setupFunction , allEffects[effectLayer].loopFunction, allEffects[effectLayer].blynkVirtualPIN, startHour, startMinute, endHour, endMinute, allEffects[effectLayer].id);
}

int findEffectIDLayerVirtualPin(int blynkVirtualPIN) {
  for ( byte i = 0 ; i < MAX_EFFECT_COUNTS ; i++ )
    if ( allEffects[i].id != -1 )
      if (allEffects[i].blynkVirtualPIN == blynkVirtualPIN)
        return i;

  return -1;
}
byte findEmptyLayer() {
  for ( byte i = 0 ; i < MAX_EFFECT_COUNTS ; i++ )
    if ( allEffects[i].id == -1 )
      return i;

  return -1;
}
void deleteLayer(byte layer) {
  if ( layer < MAX_EFFECT_COUNTS )
    allEffects[layer].id = -1;
}
#endif
