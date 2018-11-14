#include "../../include/managers/motor_manager.h"


MotorManager * MotorManager::instance = nullptr;

MotorManager * MotorManager::getInstance(){
    if(!instance)
        instance = new MotorManager();
    return instance;
}

MotorManager::MotorManager()
{
    ROS_INFO("Initializing MotorManager");
    ros::NodeHandle node_obj;
    pub_motor_coords = node_obj.advertise<std_msgs::Int32MultiArray>("motor_coords", 5);
    ROS_INFO("MotorManager initialized");
}

void MotorManager::publishCoords(int left, int right)
{
        std_msgs::Int32MultiArray msg;
        msg.data.push_back(left);
        msg.data.push_back(right);
        pub_motor_coords.publish(msg);
        ROS_INFO("Coords published (%d, %d) to /motor_coords ", left, right);
}
