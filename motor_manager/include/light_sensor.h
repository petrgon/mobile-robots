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
    LightSensor(int pinNumber) : Sensor(pinNumber, INPUT) {};

    unsigned short int checkSignal();

};

#endif /*LIGHT_SENSOR_H*/