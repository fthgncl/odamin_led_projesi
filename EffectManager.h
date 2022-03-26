#ifndef EffectManager
#define EffectManager

const bool singleUse = true;
const bool continuousUse = !singleUse;
int effectCount = 0;
bool runByTime = true;

class Effect
{
  public:
    bool enable = true;
    bool useType; // true : single use , false continuous use
    int id = -1;
    bool manualWork;
    float startTime = -1.0;
    float endTime = -1.0;


    void create(byte useType) {
      this->id = effectCount;
      this->useType = useType;
      this->manualWork = false;
      effectCount++;
    }

    void addWorkTime(byte startHour, byte startMinute, byte endHour, byte endMinute) {
      manualWork = false;
      startTime = startHour + (startMinute / 60.0);
      endTime = endHour + (endMinute / 60.0);
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

#endif
