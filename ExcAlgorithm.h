#ifndef EXC_ALGORITHM_H
#define EXC_ALGORITHM_H

#include "Algorithm.h"
#include "ExcData.h"
#include <Arduino.h>
#include "ClassFactory.h"

template <typename outData>
class SensorData;

template<int sensorCount>
class ExcAlgorithm : public Algorithm, public ClassFactory<ExcData>
{
  public:
    void call()
    {
      int perehod = 0;
      float sum = 0.;
      float dark = 0.;
      for(int i = 0; i<sensorCount; i++)
      {
        if(sensorDataPtr -> getValue(i)>black[i])
        {
          linePro[i] = 1;
        }else 
        if(sensorDataPtr -> getValue(i)<white[i])
        {
          linePro[i] = 0;
        }else
        {
          linePro[i] = float(sensorDataPtr->getValue(i)-white[i])/float(black[i] - white[i]);
          linePro[i] = constrain(linePro[i], 0, 1);
        }
      }
      for(int i = 0; i<sensorCount; i++)
      {
        sum = sum+weight[i]*linePro[i];
        dark = dark+linePro[i];
        if(i>0)
        {
          if(abs(linePro[i]-linePro[i-1])>0.7)
          {
            perehod++;
          }
        }
      }
      if (dark < .8) dark = 0;
      if((dark>0)&&(perehod<3))
      {
        sum = sum/(dark*sensorCount/2);
        data.setLastTime(millis());
        data.setValid(sum);
      }else
      {
        sum = 0;
      }
      data.setExc(sum);
      data.setDarks(dark);
      data.setExcTime(millis());
    }
    
    void init(int White[], int Black[])
    {
      for(int i = 0; i<sensorCount; i++)
      {
        white[i] = White[i];
        black[i] = Black[i];
        weight[i] = i-sensorCount/2;
        if(i>=sensorCount/2)
        {
          weight[i]++;
        }
      }
    }
    
    void setSensorDataPtr(SensorData<int>* Data)
    {
      this -> sensorDataPtr = Data;
    }
    
  private:
    SensorData<int> *sensorDataPtr;
    int white[sensorCount];
    int black[sensorCount];
    int weight[sensorCount];
    float linePro[sensorCount];
};

#endif
