#include "../../include/states/move_back_left_state.h"

MoveBackLeftState::MoveBackLeftState(Program *program) : MoveState(program, SPEED_LEFT, SPEED_RIGHT) {}

MoveBackLeftState::MoveBackLeftState(Program *program, int timeOut)
    : MoveState(program, SPEED_LEFT, SPEED_RIGHT, timeOut) {}

MoveBackLeftState::~MoveBackLeftState() {}
