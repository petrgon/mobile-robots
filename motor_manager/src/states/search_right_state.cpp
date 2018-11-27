#include "../../include/states/search_right_state.h"

SearchRightState::SearchRightState(Program *program) : State(program) {}

SearchRightState::SearchRightState(Program *program, int timeOut) : State(program, timeOut) {}

void SearchRightState::run() {}

void SearchRightState::stateInit() {
    State::stateInit();
    MotorManager::getInstance()->publishCoords(SPEED_LEFT, SPEED_RIGHT);
}

