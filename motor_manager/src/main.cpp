#include "wiringPi.h"
#include "ros/ros.h"

#include "../include/states/get_puck_state.h"
#include "../include/managers/callback_time_manager.h"
#include "../include/managers/motor_manager.h"
#include "../include/managers/sensor_manager.h"

#include <iostream>
#include <signal.h>

CallBackTimeManager *callback_manager;
MotorManager *motor_manager;
SensorManager *sensor_manager;

void SIGINT_handler(int sig)
{
    delete callback_manager; //keep order
    delete sensor_manager;
    delete motor_manager;
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
    SIGINT_handler();
    return 0;
}
