#include <ros.h>
#include <std_msgs/Int32.h>

#define enA 3
#define in1 4
#define in2 5
#define enB 9
#define in3 6
#define in4 7

ros::NodeHandle nh;

int left_motor_speed = 0;
int right_motor_speed = 0;

bool both_speeds_avalable = false;

void moveLeftMotor(const std_msgs::Int32 &number){
  left_motor_speed = number.data;
  both_speeds_avalable = false;
}  

void moveRightMotor(const std_msgs::Int32 &number){
  right_motor_speed = number.data;
  both_speeds_avalable = true;
}

ros::Subscriber<std_msgs::Int32> sub_left("left_motor", &moveLeftMotor);   
ros::Subscriber<std_msgs::Int32> sub_right("right_motor", &moveRightMotor);


void setup()
{                                           
  pinMode(enA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
                       
  pinMode(enB, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  
  nh.initNode();
  nh.subscribe(sub_left); 
  nh.subscribe(sub_right);
                            
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);  
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  analogWrite(enA, left_motor_speed);
  analogWrite(enB, right_motor_speed);
}

void loop()
{       
  if (both_speeds_avalable){  
    if (right_motor_speed < 0){  
      digitalWrite(in3, LOW);
      digitalWrite(in4, HIGH);
    } else {    
      digitalWrite(in3, HIGH);
      digitalWrite(in4, LOW);
    }
    
    if (left_motor_speed < 0){  
      digitalWrite(in1, HIGH);
      digitalWrite(in2, LOW);
    } else { 
      digitalWrite(in1, LOW);
      digitalWrite(in2, HIGH);
    }  
    analogWrite(enA, left_motor_speed);
    analogWrite(enB, right_motor_speed); 
  }
  
  nh.spinOnce();
} 
