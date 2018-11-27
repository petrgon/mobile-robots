#include "../../include/states/move_back_right_state.h"

MoveBackRightState::MoveBackRightState(Program *program) : State(program) {}

MoveBackRightState::MoveBackRightState(Program *program, int timeOut) : State(program, timeOut) {}

MoveBackRightState::~MoveBackRightState(){}

void MoveBackRightState::stateInit() {
    State::stateInit();
    MotorManager::getInstance()->publishCoords(SPEED_LEFT, SPEED_RIGHT);
}

