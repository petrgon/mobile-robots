//
// Created by Šárka on 9/29/2018.
//

#include "ros/ros.h"
#include "std_msgs/Int32.h"
#include <iostream>

void publish_number(ros::Publisher & pub) {
    int number = 0;
    std::cin >> number;
    std_msgs::Int32 msg;
    msg.data = number;
    pub.publish(msg);
}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "motor_manager");
    ros::NodeHandle node_obj;
    ros::Publisher pub_left = node_obj.advertise<std_msgs::Int32>("/left_motor", 1);
    ros::Publisher pub_right = node_obj.advertise<std_msgs::Int32>("/right_motor", 1);

    while (ros::ok())
    {
        std::cout << "Left motor speed: ";
        publish_number(pub_left);
        std::cout << "Right motor speed: ";
	    publish_number(pub_right);
        ros::spinOnce();
    }

    return 0;
}
