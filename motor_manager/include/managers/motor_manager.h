#ifndef MOTOR_MANAGER_H
#define MOTOR_MANAGER_H

#include "ros/ros.h"
#include "std_msgs/Int32MultiArray.h"

class MotorManager
{
public:

  static MotorManager* getInstance();

  ~MotorManager();

  void publishCoords(int left, int right);

private:
  MotorManager();
  ros::Publisher pub_motor_coords;
  static MotorManager * instance;

  struct Coordinates
  {
    int left;
    int right;
  };
};
#endif /*MOTOR_MANAGER_H*/