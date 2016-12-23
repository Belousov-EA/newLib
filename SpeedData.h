#ifndef SPEED_DATA
#define SPEED_DATA

#include "DataObject.h"

class SpeedData : DataObject
{
  public:
    SpeedData& operator=(SpeedData other)
    {
      if(this == &other)
      {
        return *this;
      }
      avgSpeed = other.getAvgSpeed();
      difference = other.getDifference();
      return *this;  
    }
    
    float getAvgSpeed() {return avgSpeed;};
    void setAvgSpeed(float AvgSpeed) {avgSpeed = AvgSpeed;};

     float getDifference() {return difference;};
     void setDifference(float Difference) {difference = Difference;};
  private:
    float avgSpeed;
    float difference;
};
#endif
