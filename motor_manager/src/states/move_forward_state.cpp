#include "../../include/states/move_forward_state.h"

MoveForwardState::MoveForwardState(Program *program) : State(program) {}

MoveForwardState::MoveForwardState(Program *program, int timeOut) : State(program, timeOut) {}

MoveForwardState::~MoveForwardState(){}

void MoveForwardState::stateInit() {
    State::stateInit();
    MotorManager::getInstance()->publishCoords(SPEED, SPEED);
}

