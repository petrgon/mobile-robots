#include "../../include/sensor.h"

Sensor::Sensor(int pinNumber, int mode) : pinNumber(pinNumber)
{
    pinMode(pinNumber, mode);
}

Sensor::~Sensor()
{
}
