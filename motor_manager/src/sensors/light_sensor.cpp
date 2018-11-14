#include "../../include/sensors/light_sensor.h"

LightSensor::LightSensor(int pinNumber) : Sensor(pinNumber, INPUT), previousSignal(0) {}

LightSensor::~LightSensor()  {}

unsigned short int LightSensor::checkSignal()
{
    unsigned short int lightRev = 0;
    std_msgs::Int16 light_data;
    lightRev = digitalRead(pinNumber);
    previousSignal = lightRev;
    return lightRev;
}

unsigned short int LightSensor::getPreviousSignal()
{
    return previousSignal;
}
