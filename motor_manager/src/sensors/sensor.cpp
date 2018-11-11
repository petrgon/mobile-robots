#include "../../include/sensor.h"

Sensor::Sensor(int pinNumber, int mode) : this->pinNumber = pinNumber
{
    pinMode(pinNumber, mode);
};
