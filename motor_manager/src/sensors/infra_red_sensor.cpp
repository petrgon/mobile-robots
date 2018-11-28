#include "../../include/sensors/infra_red_sensor.h"

const u_int32_t InfraRedSensor::SIGNAL_600 = 600;
const u_int32_t InfraRedSensor::SIGNAL_1500 = 1500;

InfraRedSensor::InfraRedSensor(int pinNumber) : Sensor(pinNumber, INPUT), previousSignal(0) {}

InfraRedSensor::~InfraRedSensor() {}

unsigned int InfraRedSensor::checkSignal()
{
    long long zeroCount = 0LL;
    long long oneCount = 0LL;
    auto start = std::chrono::high_resolution_clock::now();
    long long microseconds = 0LL;
    do
    {
        int input = digitalRead(pinNumber);
        ROS_DEBUG("IR Sensor input read %d", input);
        if (input)
            oneCount++;
        else
            zeroCount++;
        auto elapsed = std::chrono::high_resolution_clock::now() - start;
        microseconds = std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();
    } while (microseconds < 10000LL); //longest cycle is 3700 us
    float retVal = oneCount / (float)(oneCount + zeroCount);
    ROS_DEBUG("IR Sensor value counted %.2f", retVal);
    if (retVal > 0.17f && retVal < 0.22f)
        return 1500;
    else if (retVal > 0.27f && retVal < 0.32f)
        return 600;
    else
        return 0;
}

unsigned int InfraRedSensor::getPreviousSignal()
{
    return previousSignal;
}
