#include "wiringPi.h"
#include "ros/ros.h"
#include "../include/states/get_puck_state.h"
#include <iostream>

int main(int argc, char **argv)
{
    ros::init(argc, argv, "robot_core");
    ROS_INFO("ROS initialized");
    setenv("WIRINGPI_GPIOMEM", "1", 1);
    wiringPiSetup();
    ROS_INFO("WiringPI initialized");

    GetPuckState program;

    ROS_INFO("Entering main thread");
    while (ros::ok())
    {
        program.run();
        ros::spinOnce();
    }
    return 0;
}
