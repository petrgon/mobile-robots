#include "../../include/states/move_back_left_state.h"

MoveBackLeftState::MoveBackLeftState(Program *program) : State(program) {}

MoveBackLeftState::MoveBackLeftState(Program *program, int timeOut) : State(program, timeOut) {}

MoveBackLeftState::~MoveBackLeftState(){}

void MoveBackLeftState::stateInit() {
    State::stateInit();
    MotorManager::getInstance()->publishCoords(SPEED_LEFT, SPEED_RIGHT);
}

