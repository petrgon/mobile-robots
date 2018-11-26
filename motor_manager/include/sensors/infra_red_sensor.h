#ifndef INFRA_RED_SENSOR_H
#define INFRA_RED_SENSOR_H

#include "ros/ros.h"
#include "wiringPi.h"

#include "sensor.h"

#include <string>

class InfraRedSensor : public Sensor
{
  public:
    InfraRedSensor(int pinNumber);
    virtual ~InfraRedSensor() override;
    unsigned short int checkSignal();
    unsigned short int getPreviousSignal();

  private:
    unsigned short int previousSignal;

};

#endif /*INFRA_RED_SENSOR_H*/
