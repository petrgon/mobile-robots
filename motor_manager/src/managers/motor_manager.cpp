#include "../../include/managers/motor_manager.h"

MotorManager *MotorManager::instance = nullptr;

MotorManager::~MotorManager()
{
    publishCoords(0, 0);
    ros::spinOnce();
    usleep(250);
    ROS_INFO("MotorManager Joined");
}

MotorManager *MotorManager::getInstance()
{
    if (!instance)
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
    msg.data.clear();

    msg.layout.dim.push_back(std_msgs::MultiArrayDimension());
    msg.layout.dim[0].size = 2;
    msg.layout.dim[0].stride = 1;
    msg.layout.dim[0].label = "coords";

    msg.data.push_back(left);
    msg.data.push_back(right);
    pub_motor_coords.publish(msg);
    ROS_INFO("Coords published (%d, %d) to /motor_coords ", left, right);
}
