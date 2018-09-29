//
// Created by Šárka on 9/29/2018.
//

#include "ros/ros.h"
#include "std_msgs/Int32.h"
#include <iostream>

int main(int argc, char **argv)
{
    ros::init(argc, argv, "multiplying_publisher");
    ros::NodeHandle node_obj;
    ros::Publisher number_publisher = node_obj.advertise<std_msgs::Int32>("/numbers", 1);

    while (ros::ok())
    {
        std::cout << "Input value: ";
        int number = 0;
        std::cin >> number;

        std_msgs::Int32 msg;
        msg.data = number;
        ROS_INFO("%d", msg.data);
        number_publisher.publish(msg);
        ros::spinOnce();
    }
    return 0;
}