#include "../../include/touch_sensor.h"

bool TouchSensor::isPushed()
{
    int recvData = digitalRead(pinNumber);
    ROS_INFO("Touch sensor (pin: %d): %d ", pinNumber, recvData);
    return recvData != 0;
}
TouchSensor::~TouchSensor(){
}
