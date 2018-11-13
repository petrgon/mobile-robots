#ifndef SENSOR_H
#define SENSOR_H

#include "ros/ros.h"
#include "wiringPi.h"

class Sensor
{
  public:
    Sensor(int pinNumber, int mode);
    virtual ~Sensor() = 0;

  protected:    
    int pinNumber;

};

#endif /*SENSOR_H*/
