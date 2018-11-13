#ifndef LIGHT_SENSOR_H
#define LIGHT_SENSOR_H

#include "ros/ros.h"
#include "std_msgs/Int16.h"
#include "wiringPi.h"

#include "sensor.h"

#include <string>

class LightSensor : public Sensor
{
  public:
    LightSensor(int pinNumber);
    virtual ~LightSensor() override;
    unsigned short int checkSignal();
    unsigned short int getPreviousSignal();

  private:
    unsigned short int previousSignal;

};

#endif /*LIGHT_SENSOR_H*/
