#include "wiringPi.h"
#include "ros/ros.h"

#include "../include/states/get_puck_state.h"
#include "../include/managers/callback_time_manager.h"
#include "../include/managers/motor_manager.h"
#include "../include/managers/sensor_manager.h"

#include <iostream>
#include <signal.h>

CallBackTimeManager *callback_manager = nullptr;
MotorManager *motor_manager = nullptr;
SensorManager *sensor_manager = nullptr;

void SIGINT_handler(int sig)
{
    if (callback_manager)
    {
        delete callback_manager; //keep order
        callback_manager = nullptr;
    }
    if (sensor_manager)
    {
        delete sensor_manager;
        sensor_manager = nullptr;
    }
    if (motor_manager)
    {
        delete motor_manager;
        motor_manager = nullptr;
    }
    ros::shutdown();
}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "robot_core", ros::init_options::NoSigintHandler);
    signal(SIGINT, SIGINT_handler);
    ROS_INFO("ROS initialized");
    setenv("WIRINGPI_GPIOMEM", "1", 1);
    wiringPiSetup();
    ROS_INFO("WiringPI initialized");

    callback_manager = CallBackTimeManager::getInstance();
    motor_manager = MotorManager::getInstance();
    sensor_manager = SensorManager::getInstance();

    GetPuckState program;

    ROS_INFO("Entering main thread");
    while (ros::ok())
    {
        program.run();
        ros::spinOnce();
    }
    SIGINT_handler(15);
    return 0;
}
