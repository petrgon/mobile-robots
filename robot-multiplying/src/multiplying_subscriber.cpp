//
// Created by Šárka on 9/29/2018.
//

#include "ros/ros.h"
#include "std_msgs/Int32.h"
#include <iostream>
void number_callback(const std_msgs::Int32::ConstPtr& msg)
{
    ROS_INFO("Received [%d]", msg->data);
}


int main(int argc, char **argv)
{
    ros::init(argc, argv, "multiplying_subscriber");
    ros::NodeHandle node_obj;
    ros::Subscriber number_subscriber =
            node_obj.subscribe("/numbers", 1, number_callback);

    return 0;
}