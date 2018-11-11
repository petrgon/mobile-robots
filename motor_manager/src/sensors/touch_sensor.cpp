#include "../../include/touch_sensor.h"

bool TouchSensor::isPushed()
{
    // todo
    return digitalRead(pinNumber) != 0;
}
