#ifndef MOTORS_H
#define MOTORS_H

#include <Arduino.h>
#include "Actuator.h"

class SpeedData;

class Motors : public Actuator
{
  public:
    void init(int lp, int ld, int rp, int rd)
    {
      rightPowerPin = rp;
      rightDirectionPin = rd;
      leftPowerPin = lp;
      leftDirectionPin = ld;
    }
    
    void call()
    {
      right = speedData->getAvgSpeed()*(1+speedData->getDifference());
      left = speedData->getAvgSpeed()*(1-speedData->getDifference());
      if(right<0)
      {
        digitalWrite(rightDirectionPin, LOW);
      }else
      {
        digitalWrite(rightDirectionPin, HIGH);
      }
      if (left>0)
      {
        digitalWrite(leftDirectionPin, LOW);
      }else
      {
        digitalWrite(leftDirectionPin, HIGH);
      }
      analogWrite(rightPowerPin, int(constrain(abs(right*255), 0, 255)) );
      analogWrite(leftPowerPin, int(constrain(abs(left*255), 0, 255)) );
    }
    
    void setSpeedData(SpeedData* data)
    {
      speedData = data;
    }
  private:
    float right;
    float left;
    SpeedData*speedData;
    int leftPowerPin;
    int rightPowerPin;
    int leftDirectionPin;
    int rightDirectionPin;
};

#endif
