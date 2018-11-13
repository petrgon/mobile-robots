#include "../../include/sensors/touch_sensor.h"

TouchSensor::TouchSensor(int pinNumber) : Sensor(pinNumber, INPUT), previousValue(false) {}

TouchSensor::~TouchSensor() {}

bool TouchSensor::isPushed()
{
    int recvData = digitalRead(pinNumber);
    ROS_INFO("Touch sensor (pin: %d): %d ", pinNumber, recvData);
    return previousValue = recvData != 0;
}
bool TouchSensor::getPrevious()
{
    return previousValue;
}
