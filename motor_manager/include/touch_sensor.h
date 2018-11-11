#ifndef TOUCH_SENSOR_H
#define TOUCH_SENSOR_H

#include "ros/ros.h"
#include "wiringPi.h"
#include <string>

class TouchSensor : public Sensor
{
  public:
    TouchSensor(int pinNumber) : Sensor(pinNumber, INPUT) {};

    bool isPushed();

};

#endif /*TOUCH_SENSOR_H*/