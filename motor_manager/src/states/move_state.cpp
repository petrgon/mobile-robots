#include "../../include/states/move_state.h"

MoveState::MoveState(Program *program, int leftSpeed, int rightSpeed) : State(program),
                                                                        leftWheelSpeed(leftSpeed),
                                                                        rightWheelSpeed(rightSpeed) {}

MoveState::MoveState(Program *program, int leftSpeed, int rightSpeed, int timeOut) : State(program, timeOut),
                                                                                     leftWheelSpeed(leftSpeed),
                                                                                     rightWheelSpeed(rightSpeed)
{
}

MoveState::~MoveState() {}

void MoveState::stateInit()
{
    State::stateInit();
    MotorManager::getInstance()->publishCoords(leftWheelSpeed, rightWheelSpeed);
}
