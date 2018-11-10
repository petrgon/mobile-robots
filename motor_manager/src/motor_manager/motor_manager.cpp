#include "../../include/motor_manager.h"

MotorManager::MotorManager(int argc, char **argv)
{
    ros::init(argc, argv, "motor_manager");
    ros::NodeHandle node_obj;
    ros::Publisher pub_motor_coords = node_obj.advertise<std_msgs::Int32MultiArray>("/motor_coords", 1);
}

void MotorManager::publishCoords(int left, int right)
{
    if (ros::ok())
    {
        Coordinates coord = {.left = left, .right = right};
        std_msgs::Int32MultiArray msg;
        msg.data.push_back(coord.left);
        msg.data.push_back(coord.right);
        pub_motor_coords.publish(msg);
        ros::spinOnce();
    }
}
