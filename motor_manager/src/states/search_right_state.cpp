#include "../../include/states/search_right_state.h"

SearchRightState::SearchRightState(Program *program) : MoveState(program, SPEED_LEFT, SPEED_RIGHT) {}

SearchRightState::SearchRightState(Program *program, int timeOut)
    : MoveState(program, SPEED_LEFT, SPEED_RIGHT, timeOut) {}

SearchRightState::~SearchRightState() {}
