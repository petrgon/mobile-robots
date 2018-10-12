#include <ros.h>
#include <std_msgs/Int32.h>

ros::NodeHandle nh;

std_msgs::Int32 multiplyed_number;

ros::Publisher pub("multiplyed", &multiplyed_number);

void messageCb(const std_msgs::Int32 &number){
  multiplyed_number.data = number.data * 2;
  pub.publish(&multiplyed_number);
  nh.spinOnce();
}

ros::Subscriber<std_msgs::Int32> sub("number", &messageCb);

void setup()
{
 nh.initNode();
 nh.subscribe(sub);
 nh.advertise(pub);
}
void loop()
{
 nh.spinOnce();
} 
