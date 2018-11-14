#include <ros.h>
#include <std_msgs/Int32MultiArray.h>

#define enA 3
#define in1 4
#define in2 5
#define enB 9
#define in3 6
#define in4 7

#define ABS(x) ((x) > 0 ? (x) : -(x))
#define MIN(x, y) x < y ? x : y
#define MAX(x, y) x > y ? x : y

#define RIGHT_WHEEL_CALIBRATION 1.045
#define LEFT_WHEEL_CALIBRATION 0.955
#define MAX_VELOCITY 244

struct Coordinates
{
  Coordinates() : left(0), right(0) {}
  int left;
  int right;
};

ros::NodeHandle nh;
Coordinates coord;

void getCoordsHandler(const std_msgs::Int32MultiArray &input)
{
  coord.left = input.data[0];
  coord.right = input.data[1];
}

ros::Subscriber<std_msgs::Int32MultiArray> sub_motor_coords("motor_coords", &getCoordsHandler);

void setup()
{
  pinMode(enA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);

  pinMode(enB, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);

  nh.initNode();
  nh.subscribe(sub_motor_coords);
}

void loop()
{
  if (coord.left < 0)
  {
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);
  }
  else
  {
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);
  }

  if (coord.right < 0)
  {
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
  }
  else
  {
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
  }
  analogWrite(enA, MIN(ABS(coord.left) * LEFT_WHEEL_CALIBRATION, MAX_VELOCITY));
  analogWrite(enB, MIN(ABS(coord.right) * RIGHT_WHEEL_CALIBRATION, MAX_VELOCITY));

  nh.spinOnce();
}
