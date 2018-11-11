#include "../include/motor_manager.h"
#include <iostream>

int main(int argc, char ** argv){
    MotorManager motor(argc, argv);
    int coord_left = 0, coord_right = 0;
    while(1) {
        std::cin >> coord_left >> coord_right;
        motor.publishCoords(coord_left,coord_right);
    }
    return 0;
}