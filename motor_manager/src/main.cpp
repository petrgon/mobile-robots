#include "../include/motor_manager.h"
#include "../include/sensor_manager.h"
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
    MotorManager motor;
    SensorManager sensor;
    sensor.start();
    int coord_left = 100, coord_right = 100;
    ROS_INFO("Entering main thread");
    while (ros::ok())
    {
        std::cin >> coord_left >> coord_right;
        motor.publishCoords(coord_left, coord_right);
        ros::spinOnce();
    }
    return 0;
}