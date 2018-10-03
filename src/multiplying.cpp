//
// Created by Šárka on 9/29/2018.
//

#include "ros/ros.h"
#include "std_msgs/Int32.h"
#include <iostream>

bool messageRecieved;

void publish_number(ros::Publisher & pub) {
    std::cout << "Input value: ";
    int number = 0;
    std::cin >> number;
    std_msgs::Int32 msg;
    msg.data = number;
    pub.publish(msg);
}


void number_callback(const std_msgs::Int32::ConstPtr& msg)
{
    std::cout << "Received " <<  msg->data << "\n";
    messageRecieved = 1;
}


int main(int argc, char **argv)
{
    messageRecieved = 1;
    ros::init(argc, argv, "multiplying");
    ros::NodeHandle node_obj;
    ros::Subscriber sub = node_obj.subscribe("/multiplyed", 1, number_callback);
    ros::Publisher pub = node_obj.advertise<std_msgs::Int32>("/number", 1);

    while (ros::ok())
    {
	if (messageRecieved){
	    publish_number(pub);
	    messageRecieved = 0;
	}
        ros::spinOnce();
    }

    return 0;
}
