#ifndef SPEED_ALGORITHM_H
#define SPEED_ALGORITHM_H

#include "Algorithm.h"
#include "SpeedData.h"
#include "ClassFactory.h"

class ExcData;

class SpeedAlgorithm : public Algorithm, public ClassFactory<SpeedData>
{
  public:
    void init(float P, float D, float MidSpeed, unsigned long VozvratTime)
    {
      p = P;
      d = D;
      midSpeed = MidSpeed;
      vozvratTime = VozvratTime;
    }
    
    void call()
    {
      if(excData->getDarks()!=0)
      {
        data.setDifference ( excData -> getExc()*p+(excData -> getExc()-lastExc)*d/(excData->getExcTime() - lastTime));
    
        lastTime = excData->getExcTime();
        lastExc = excData->getExc();
      }else
      {
        vozvrat();
      }      
      data.setAvgSpeed(midSpeed);   
    }

    void vozvrat()
    {
      if(excData->getExcTime()-excData->getLastTime()>vozvratTime)
      {
        if(excData->getValid()>0)
        {
          data.setDifference(p);
          lastExc = 1.00;
        }else
        {
          data.setDifference(-p);
          lastExc = -1.00;
        }
      }
    }
    
    void setExcDataPtr(ExcData* data)
    {
      this -> excData = data;
    }
    
  private:
    float p;
    float d;
    float midSpeed;
    unsigned long vozvratTime;
    ExcData* excData;
    float lastExc;
    unsigned long lastTime;
};

#endif
