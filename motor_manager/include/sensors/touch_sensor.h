#ifndef TOUCH_SENSOR_H
#define TOUCH_SENSOR_H

#include "ros/ros.h"
#include "wiringPi.h"
#include "sensor.h"

#include <string>

class TouchSensor : public Sensor
{
  public:
    TouchSensor(int pinNumber);
    virtual ~TouchSensor() override;
    bool isPushed();
    bool getPrevious();
  private:
    bool previousValue;

};

#endif /*TOUCH_SENSOR_H*/
