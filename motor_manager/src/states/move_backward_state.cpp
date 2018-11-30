#include "../../include/states/move_backward_state.h"

MoveBackwardState::MoveBackwardState(Program *program) : MoveState(program, SPEED, SPEED) {}

MoveBackwardState::MoveBackwardState(Program *program, int timeOut)
    : MoveState(program, SPEED, SPEED, timeOut) {}

MoveBackwardState::~MoveBackwardState() {}
