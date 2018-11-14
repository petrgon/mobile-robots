#include "../../include/sensors/touch_sensor.h"

TouchSensor::TouchSensor(int pinNumber) : Sensor(pinNumber, INPUT), previousValue(false) {}

TouchSensor::~TouchSensor() {}

bool TouchSensor::isPushed()
{
    int recvData = digitalRead(pinNumber);
    return previousValue = recvData != 0;
}
bool TouchSensor::getPrevious()
{
    return previousValue;
}
