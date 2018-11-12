#include "../../include/light_sensor.h"

unsigned short int LightSensor::checkSignal()
{
    unsigned short int light_rev = 0;
    std_msgs::Int16 light_data;
    light_rev = digitalRead(pinNumber) ;
    ROS_INFO("light_receive: %d ", light_rev);
}
LightSensor::~LightSensor(){
}
