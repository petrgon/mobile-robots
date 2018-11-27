#include "../../include/states/state.h"

State::State(Program *program) : SensorObserver(), program(program), timeOut(-1), isActive(false) {}

State::State(Program *program, int timeOut) : SensorObserver(), program(program), timeOut(timeOut), isActive(false) {}

State::~State(){
    unsubscribe();
}

State *State::setTimeElapsedNextState(State *nextState)
{
    timeElapsedNextState = nextState;
    return this;
}

State *State::setPuckAquiredNextState(State *nextState)
{
    SensorManager::getInstance()->subscribePuckAquiredEvent(this);
    puckAquiredNextState = nextState;
    return this;
}
State *State::setPuckLostNextState(State *nextState)
{
    SensorManager::getInstance()->subscribePuckLostEvent(this);
    puckLostNextState = nextState;
    return this;
}

State *State::setLightDetectedNextState(State *nextState)
{
    SensorManager::getInstance()->subscribeLightDetectedEvent(this);
    lightDetectedNextState = nextState;
    return this;
}
State *State::setLightLostNextState(State *nextState)
{
    SensorManager::getInstance()->subscribeLightLostEvent(this);
    lightLostNextState = nextState;
    return this;
}

State *State::setLeftTouchTriggeredNextState(State *nextState)
{
    SensorManager::getInstance()->subscribeLeftTouchTriggeredEvent(this);
    leftTouchTriggeredNextState = nextState;
    return this;
}
State *State::setLeftTouchFreedNextState(State *nextState)
{
    SensorManager::getInstance()->subscribeLeftTouchFreedEvent(this);
    leftTouchFreedNextState = nextState;
    return this;
}

State *State::setRightTouchTriggeredNextState(State *nextState)
{
    SensorManager::getInstance()->subscribeRightTouchTriggeredEvent(this);
    rightTouchTriggeredNextState = nextState;
    return this;
}
State *State::setRightTouchFreedNextState(State *nextState)
{
    SensorManager::getInstance()->subscribeRightTouchFreedEvent(this);
    rightTouchFreedNextState = nextState;
    return this;
}

State *State::setBothTouchTriggeredNextState(State *nextState)
{
    SensorManager::getInstance()->subscribeBothTouchTriggeredEvent(this);
    bothTouchTriggeredNextState = nextState;
    return this;
}
State *State::setBothTouchFreedNextState(State *nextState)
{
    SensorManager::getInstance()->subscribeBothTouchFreedEvent(this);
    bothTouchFreedNextState = nextState;
    return this;
}

State *State::setIr600FoundNextState(State *nextState)
{
    SensorManager::getInstance()->subscribeIR600FoundEvent(this);
    ir600FoundNextState = nextState;
    return this;
}
State *State::setIr600LostNextState(State *nextState)
{
    SensorManager::getInstance()->subscribeIR600LostEvent(this);
    ir600LostNextState = nextState;
    return this;
}

State *State::setIr1500FoundNextState(State *nextState)
{
    SensorManager::getInstance()->subscribeIR1500FoundEvent(this);
    ir1500FoundNextState = nextState;
    return this;
}
State *State::setIr1500LostNextState(State *nextState)
{
    SensorManager::getInstance()->subscribeIR1500LostEvent(this);
    ir1500LostNextState = nextState;
    return this;
}

void State::timeElapsedEventHandler()
{
    if (isActive && timeElapsedNextState){
        program->changeState(timeElapsedNextState);
        isActive = false;
    }
}

void State::puckAquiredEventHandler()
{
    if (isActive && puckAquiredNextState){
        program->changeState(puckAquiredNextState);
        isActive = false;
    }
}
void State::puckLostEventHandler()
{
    if (isActive && puckLostNextState){
        program->changeState(puckLostNextState);
        isActive = false;
    }
}

void State::lightDetectedEventHandler()
{
    if (isActive && lightDetectedNextState){
        program->changeState(lightDetectedNextState);
        isActive = false;
    }
}
void State::lightLostEventHandler()
{
    if (isActive && lightLostNextState){
        program->changeState(lightLostNextState);
        isActive = false;
    }
}

void State::leftTouchTriggeredEventHandler()
{
    if (isActive && leftTouchFreedNextState){
        program->changeState(leftTouchFreedNextState);
        isActive = false;
    }
}
void State::leftTouchFreedEventHandler()
{
    if (isActive && leftTouchFreedNextState){
        program->changeState(leftTouchFreedNextState);
        isActive = false;
    }
}

void State::rightTouchTriggeredEventHandler()
{
    if (isActive && rightTouchTriggeredNextState){
        program->changeState(rightTouchTriggeredNextState);
        isActive = false;
    }
}
void State::rightTouchFreedEventHandler()
{
    if (isActive && rightTouchFreedNextState){
        program->changeState(rightTouchFreedNextState);
        isActive = false;
    }
}

void State::bothTouchTriggeredEventHandler()
{
    if (isActive && bothTouchTriggeredNextState){
        program->changeState(bothTouchTriggeredNextState);
        isActive = false;
    }
}
void State::bothTouchFreedEventHandler()
{
    if (isActive && bothTouchFreedNextState){
        program->changeState(bothTouchFreedNextState);
        isActive = false;
    }
}

void State::ir600FoundEventHandler()
{
    if (isActive && ir600FoundNextState){
        program->changeState(ir600FoundNextState);
        isActive = false;
    }
}
void State::ir600LostEventHandler()
{
    if (isActive && ir600LostNextState){
        program->changeState(ir600LostNextState);
        isActive = false;
    }
}

void State::ir1500FoundEventHandler()
{
    if (isActive && ir1500FoundNextState){
        program->changeState(ir1500FoundNextState);
        isActive = false;
    }
}
void State::ir1500LostEventHandler()
{
    if (isActive && ir1500LostNextState){
        program->changeState(ir1500LostNextState);
        isActive = false;
    }
}

void State::stateInit()
{
    isActive = true;
    if (timeOut > 0){
        CallBackTimeManager::getInstance()->subscribe(this, timeOut);
    }
}

void State::unsubscribe() {
    CallBackTimeManager::getInstance()->unsubscribe(this);
    SensorManager::getInstance()->unsubscribeFromAll(this);
}
