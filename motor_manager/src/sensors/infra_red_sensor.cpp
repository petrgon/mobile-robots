#include "../../include/sensors/infra_red_sensor.h"

InfraRedSensor::InfraRedSensor(int pinNumber) : Sensor(pinNumber, INPUT), previousSignal(0) {}

InfraRedSensor::~InfraRedSensor()  {}

unsigned short int InfraRedSensor::checkSignal()
{
    unsigned short int lightRev = 0;
    lightRev = digitalRead(pinNumber);
    previousSignal = lightRev;
    return lightRev;
}

unsigned short int InfraRedSensor::getPreviousSignal()
{
    return previousSignal;
}
