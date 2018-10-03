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
    ros::init(argc, argv, "multiplying");
    ros::NodeHandle node_obj;
    ros::Subscriber sub = node_obj.subscribe("/multiplyed", 1, number_callback);
    ros::Publisher pub = node_obj.advertise<std_msgs::Int32>("/number", 1);


    while (ros::ok())
    {
        std::cout << "Input value: ";
        int number = 0;
        std::cin >> number;

        std_msgs::Int32 msg;
        msg.data = number;
        ROS_INFO("%d", msg.data);
        pub.publish(msg);
        ros::spinOnce();
    }

    return 0;
}
