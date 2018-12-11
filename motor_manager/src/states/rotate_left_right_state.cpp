#include "../../include/states/rotate_left_right_state.h"

RotateLeftRightState::RotateLeftRightState(Program *program) : MoveState(program, SPEED_A, SPEED_B), speedALeft(true) {}

RotateLeftRightState::RotateLeftRightState(Program *program, int timeOut)
    : MoveState(program, SPEED_A, SPEED_B, timeOut), speedALeft(true) {}

RotateLeftRightState::~RotateLeftRightState() {}

void RotateLeftRightState::stateInit()
{
    State::stateInit();
    if (speedALeft){
        MotorManager::getInstance()->publishCoords(SPEED_A, SPEED_B);
    } else {
        MotorManager::getInstance()->publishCoords(SPEED_B, SPEED_A);
    }
    speedALeft = !speedALeft;
}