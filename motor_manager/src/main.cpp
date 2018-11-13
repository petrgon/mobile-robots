#include "wiringPi.h"
#include "ros/ros.h"
#include <iostream>

int main(int argc, char **argv)
{
    ros::init(argc, argv, "robot_core");
    ROS_INFO("ROS initialized");
    setenv("WIRINGPI_GPIOMEM", "1", 1);
    wiringPiSetup();
    ROS_INFO("WiringPI initialized");

    ROS_INFO("Entering main thread");
    while (ros::ok())
    {
        ros::spinOnce();
    }
    return 0;
}
