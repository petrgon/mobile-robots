#include "../../include/states/state.h"
#include "../../include/programs/program.h"

State::State(Program *program) : SensorObserver(), program(program), timeOut(-1), isActive(false),
                                 timeElapsedNextState(nullptr), puckAquiredNextState(nullptr),
                                 puckLostNextState(nullptr), lightDetectedNextState(nullptr),
                                 lightLostNextState(nullptr), leftTouchTriggeredNextState(nullptr),
                                 leftTouchFreedNextState(nullptr), rightTouchTriggeredNextState(nullptr),
                                 rightTouchFreedNextState(nullptr), bothTouchTriggeredNextState(nullptr),
                                 bothTouchFreedNextState(nullptr), ir600FoundNextState(nullptr),
                                 ir600LostNextState(nullptr), ir1500FoundNextState(nullptr),
                                 ir1500LostNextState(nullptr) {}

State::State(Program *program, int timeOut) : SensorObserver(), program(program), timeOut(timeOut), isActive(false),
                                 timeElapsedNextState(nullptr), puckAquiredNextState(nullptr),
                                 puckLostNextState(nullptr), lightDetectedNextState(nullptr),
                                 lightLostNextState(nullptr), leftTouchTriggeredNextState(nullptr),
                                 leftTouchFreedNextState(nullptr), rightTouchTriggeredNextState(nullptr),
                                 rightTouchFreedNextState(nullptr), bothTouchTriggeredNextState(nullptr),
                                 bothTouchFreedNextState(nullptr), ir600FoundNextState(nullptr),
                                 ir600LostNextState(nullptr), ir1500FoundNextState(nullptr),
                                 ir1500LostNextState(nullptr) {}

State::~State()
{
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

State *State::setCollisionNextState(State *nextState){
    setLeftTouchTriggeredNextState(nextState);
    setRightTouchTriggeredNextState(nextState);
    setBothTouchTriggeredNextState(nextState);
    return this;
}

void State::timeElapsedEventHandler()
{
    if (isActive && timeElapsedNextState)
    {
        ROS_INFO("Changinch state: TIMEOUT");
        isActive = false;
        program->changeState(timeElapsedNextState);
    }
}

void State::puckAquiredEventHandler()
{
    if (isActive && puckAquiredNextState)
    {
        isActive = false;
        program->changeState(puckAquiredNextState);
    }
}
void State::puckLostEventHandler()
{
    if (isActive && puckLostNextState)
    {
        isActive = false;
        program->changeState(puckLostNextState);
    }
}

void State::lightDetectedEventHandler()
{
    if (isActive && lightDetectedNextState)
    {
        isActive = false;
        program->changeState(lightDetectedNextState);
    }
}
void State::lightLostEventHandler()
{
    if (isActive && lightLostNextState)
    {
        isActive = false;
        program->changeState(lightLostNextState);
    }
}

void State::leftTouchTriggeredEventHandler()
{
    if (isActive && leftTouchTriggeredNextState)
    {
        isActive = false;
        program->changeState(leftTouchTriggeredNextState);
    }
}
void State::leftTouchFreedEventHandler()
{
    if (isActive && leftTouchFreedNextState)
    {
        isActive = false;
        program->changeState(leftTouchFreedNextState);
    }
}

void State::rightTouchTriggeredEventHandler()
{
    if (isActive && rightTouchTriggeredNextState)
    {
        isActive = false;
        program->changeState(rightTouchTriggeredNextState);
    }
}
void State::rightTouchFreedEventHandler()
{
    if (isActive && rightTouchFreedNextState)
    {
        isActive = false;
        program->changeState(rightTouchFreedNextState);
    }
}

void State::bothTouchTriggeredEventHandler()
{
    if (isActive && bothTouchTriggeredNextState)
    {
        isActive = false;
        program->changeState(bothTouchTriggeredNextState);
    }
}
void State::bothTouchFreedEventHandler()
{
    if (isActive && bothTouchFreedNextState)
    {
        isActive = false;
        program->changeState(bothTouchFreedNextState);
    }
}

void State::ir600FoundEventHandler()
{
    if (isActive && ir600FoundNextState)
    {
        isActive = false;
        program->changeState(ir600FoundNextState);
    }
}
void State::ir600LostEventHandler()
{
    if (isActive && ir600LostNextState)
    {
        isActive = false;
        program->changeState(ir600LostNextState);
    }
}

void State::ir1500FoundEventHandler()
{
    if (isActive && ir1500FoundNextState)
    {
        isActive = false;
        program->changeState(ir1500FoundNextState);
    }
}
void State::ir1500LostEventHandler()
{
    if (isActive && ir1500LostNextState)
    {
        isActive = false;
        program->changeState(ir1500LostNextState);
    }
}

void State::stateInit()
{
    isActive = true;
    if (timeOut > 0)
    {
        CallBackTimeManager::getInstance()->subscribe(this, timeOut);
    }
}

void State::unsubscribe()
{
    CallBackTimeManager::getInstance()->unsubscribe(this);
    SensorManager::getInstance()->unsubscribeFromAll(this);
}

void State::run() {}
