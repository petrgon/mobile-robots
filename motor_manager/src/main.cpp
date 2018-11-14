#include "wiringPi.h"
#include "ros/ros.h"

#include "../include/states/get_puck_state.h"
#include "../include/managers/callback_time_manager.h"
#include "../include/managers/motor_manager.h"
#include "../include/managers/sensor_manager.h"

#include <iostream>

int main(int argc, char **argv)
{
    ros::init(argc, argv, "robot_core");
    ROS_INFO("ROS initialized");
    setenv("WIRINGPI_GPIOMEM", "1", 1);
    wiringPiSetup();
    ROS_INFO("WiringPI initialized");

    CallBackTimeManager *callback_manager = CallBackTimeManager::getInstance();
    MotorManager *motor_manager = MotorManager::getInstance();
    SensorManager *sensor_manager = SensorManager::getInstance();

    GetPuckState program;

    ROS_INFO("Entering main thread");
    while (ros::ok())
    {
        program.run();
        ros::spinOnce();
    }
    delete callback_manager;
    delete motor_manager;
    delete sensor_manager;
    return 0;
}
