#include "../../include/states/move_backward_state.h"

MoveBackwardState::MoveBackwardState(Program *program) : State(program) {}

MoveBackwardState::MoveBackwardState(Program *program, int timeOut) : State(program, timeOut) {}

void MoveBackwardState::run() {}

void MoveBackwardState::stateInit() {
    State::stateInit();
    MotorManager::getInstance()->publishCoords(SPEED, SPEED);
}

