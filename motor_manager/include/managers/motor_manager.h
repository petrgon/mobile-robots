#ifndef MOTOR_MANAGER_H
#define MOTOR_MANAGER_H

#include "ros/ros.h"
#include "std_msgs/Int32MultiArray.h"

class MotorManager
{
  public:
    MotorManager();

    void publishCoords(int left, int right);

  private:    
    ros::Publisher pub_motor_coords;

    struct Coordinates
    {
        int left;
        int right;
    };
};
#endif /*MOTOR_MANAGER_H*/