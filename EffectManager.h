#ifndef EffectManager
#define EffectManager

const bool singleUse = true;
const bool continuousUse = !singleUse;

class Effect
{
  public:
    bool enable = true;
    bool useType; // true : single use , false continuous use
    int EffectID;
    bool clockwork;
    float startTime = -1.0;
    float endTime = -1.0;


    void create(int EffectID, byte useType, bool clockwork) {
      this->EffectID = EffectID;
      this->useType = useType;
      this->clockwork = clockwork;

    }

    void addWorkTime(byte startHour, byte startMinute, byte endHour, byte endMinute) {
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
