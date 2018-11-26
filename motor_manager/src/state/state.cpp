#include "../../include/states/state.h"

State::State(Program * program) : SensorObserver(), program(program){}

void State::stateInit(){
    subscribe();
}

void State::subscribe(){}

void State::unsubscribe(){}