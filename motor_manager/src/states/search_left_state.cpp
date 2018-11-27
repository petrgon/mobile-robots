#include "../../include/states/search_left_state.h"

SearchLeftState::SearchLeftState(Program *program) : State(program) {}

SearchLeftState::SearchLeftState(Program *program, int timeOut) : State(program, timeOut) {}

void SearchLeftState::run() {}

void SearchLeftState::stateInit() {
    State::stateInit();
    MotorManager::getInstance()->publishCoords(SPEED_LEFT, SPEED_RIGHT);
}

