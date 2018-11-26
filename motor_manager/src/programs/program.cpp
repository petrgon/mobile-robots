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
    if (nextState < stateConut){
        actualState->unsubscribe();
        actualState = &allStates[nextState];
        nextState = stateConut;
        actualState->stateInit();
    }
    actualState->run();
}

void Program::changeState(unsigned int nextState){
    this->nextState = nextState; 
}