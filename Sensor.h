#ifndef SENSOR_H
#define SENSOR_H

#include <Arduino.h>
#include "SensorData.h"
#include "Algorithm.h"
#include "ClassFactory.h"

template <typename T, int sensorCount>
class Sensor : public ClassFactory<SensorData<int>>
{
  public:
    void call()
    {
      for(int i = 0; i<sensorCount; i++)
      {
        data.setValue(analogRead(sensors[i]), i);
      }
    }


    
    void init(int Sensors[])
    {
      data.init(sensorCount);
      for(int i=0; i<sensorCount; i++)
      {
        sensors[i] = Sensors[i];
      }
    }
  private:
    int sensors[sensorCount];
};
#endif
