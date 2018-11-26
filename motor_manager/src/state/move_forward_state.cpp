#include "../../include/states/move_forward_state.h"

MoveForwardState::MoveForwardState(Program *program) : State(program) {}

void MoveForwardState::run() {}

void MoveForwardState::stateInit() {
    State::stateInit();
    MotorManager::getInstance()->publishCoords(SPEED, SPEED);
    CallBackTimeManager::getInstance()->subscribe(this, TIME_OUT);
}

void State::subscribe(){
    State::subscribe();
}

void State::unsubscribe(){
    CallBackTimeManager::getInstance()->unsubscribe(this);
}

