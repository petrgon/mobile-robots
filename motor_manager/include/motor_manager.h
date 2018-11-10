#ifndef MOTOR_PUBLISHER_H
#define MOTOR_PUBLISHER_H

#include "ros/ros.h"
#include "std_msgs/Int32MultiArray.h"

class MotorManager
{
  public:
    MotorManager(int argc, char **argv);

    void publishCoords(int left, int right);

  private:    
    ros::Publisher pub_motor_coords;

    struct Coordinates
    {
        int left;
        int right;
    };
};
#endif /*MOTOR_PUBLISHER_H*/