#include "../../include/programs/program.h"

Program::Program() : SensorObserver()
{
}

Program::~Program() {
    if (allStates != nullptr){
        delete [] allStates;
    }
}

void Program::run(){
    if (nextState != nullptr){
        actualState = nextState;
        nextState = nullptr;
        actualState->stateInit();
    }
    actualState->run();
}

void Program::changeState(State *nextState){
    this->nextState = nextState; 
}