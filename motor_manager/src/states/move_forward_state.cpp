#include "../../include/states/move_forward_state.h"

MoveForwardState::MoveForwardState(Program *program) : MoveState(program, SPEED, SPEED) {}

MoveForwardState::MoveForwardState(Program *program, int timeOut)
    : MoveState(program, SPEED + 5, SPEED, timeOut) {} //TODO FIXME

MoveForwardState::~MoveForwardState() {}
