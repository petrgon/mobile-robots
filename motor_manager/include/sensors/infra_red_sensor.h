#ifndef INFRA_RED_SENSOR_H
#define INFRA_RED_SENSOR_H

#include "ros/ros.h"
#include "wiringPi.h"

#include "sensor.h"
#include <chrono>
#include <string>

class InfraRedSensor : public Sensor
{
  public:
    InfraRedSensor(int pinNumber);
    virtual ~InfraRedSensor() override;
    unsigned int checkSignal();
    unsigned int getPreviousSignal();

    static const u_int32_t SIGNAL_600;
    static const u_int32_t SIGNAL_1500;

  private:
    unsigned short int previousSignal;

};

#endif /*INFRA_RED_SENSOR_H*/
