#include "../../include/sensors/infra_red_sensor.h"

const u_int32_t InfraRedSensor::SIGNAL_600 = 600;
const u_int32_t InfraRedSensor::SIGNAL_1500 = 1500;

InfraRedSensor::InfraRedSensor(int pinNumber) : Sensor(pinNumber, INPUT), previousSignal(0) {}

InfraRedSensor::~InfraRedSensor() {}

unsigned int InfraRedSensor::checkSignal()
{ //TODO make a desision
    unsigned short int lightRev = 0;
    lightRev = digitalRead(pinNumber);
    previousSignal = lightRev;
    return lightRev;
}

unsigned int InfraRedSensor::getPreviousSignal()
{
    return previousSignal;
}
