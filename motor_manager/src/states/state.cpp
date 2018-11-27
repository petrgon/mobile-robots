#include "../../include/states/state.h"

State::State(Program *program) : SensorObserver(), program(program), timeOut(-1) {}

State::State(Program *program, int timeOut) : SensorObserver(), program(program), timeOut(timeOut) {}

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
    if (timeElapsedNextState)
        program->changeState(timeElapsedNextState);
}

void State::puckAquiredEventHandler()
{
    if (puckAquiredNextState)
        program->changeState(puckAquiredNextState);
}
void State::puckLostEventHandler()
{
    if (puckLostNextState)
        program->changeState(puckLostNextState);
}

void State::lightDetectedEventHandler()
{
    if (lightDetectedNextState)
        program->changeState(lightDetectedNextState);
}
void State::lightLostEventHandler()
{
    if (lightLostNextState)
        program->changeState(lightLostNextState);
}

void State::leftTouchTriggeredEventHandler()
{
    if (leftTouchFreedNextState)
        program->changeState(leftTouchFreedNextState);
}
void State::leftTouchFreedEventHandler()
{
    if (leftTouchFreedNextState)
        program->changeState(leftTouchFreedNextState);
}

void State::rightTouchTriggeredEventHandler()
{
    if (rightTouchTriggeredNextState)
        program->changeState(rightTouchTriggeredNextState);
}
void State::rightTouchFreedEventHandler()
{
    if (rightTouchFreedNextState)
        program->changeState(rightTouchFreedNextState);
}

void State::bothTouchTriggeredEventHandler()
{
    if (bothTouchTriggeredNextState)
        program->changeState(bothTouchTriggeredNextState);
}
void State::bothTouchFreedEventHandler()
{
    if (bothTouchFreedNextState)
        program->changeState(bothTouchFreedNextState);
}

void State::ir600FoundEventHandler()
{
    if (ir600FoundNextState)
        program->changeState(ir600FoundNextState);
}
void State::ir600LostEventHandler()
{
    if (ir600LostNextState)
        program->changeState(ir600LostNextState);
}

void State::ir1500FoundEventHandler()
{
    if (ir1500FoundNextState)
        program->changeState(ir1500FoundNextState);
}
void State::ir1500LostEventHandler()
{
    if (ir1500LostNextState)
        program->changeState(ir1500LostNextState);
}

void State::stateInit()
{
    if (timeOut > 0){
        CallBackTimeManager::getInstance()->subscribe(this, timeOut);
    }
}

void State::unsubscribe() {
    CallBackTimeManager::getInstance()->unsubscribe(this);
    SensorManager::getInstance()->unsubscribeFromAll(this);
}
