#include "../../include/states/move_back_right_state.h"

MoveBackRightState::MoveBackRightState(Program *program) : MoveState(program, SPEED_LEFT, SPEED_RIGHT) {}

MoveBackRightState::MoveBackRightState(Program *program, int timeOut)
    : MoveState(program, SPEED_LEFT, SPEED_RIGHT, timeOut) {}

MoveBackRightState::~MoveBackRightState() {}
