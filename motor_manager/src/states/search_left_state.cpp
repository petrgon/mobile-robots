#include "../../include/states/search_left_state.h"

SearchLeftState::SearchLeftState(Program *program) : MoveState(program, SPEED_LEFT, SPEED_RIGHT) {}

SearchLeftState::SearchLeftState(Program *program, int timeOut)
    : MoveState(program, SPEED_LEFT, SPEED_RIGHT, timeOut) {}

SearchLeftState::~SearchLeftState() {}
