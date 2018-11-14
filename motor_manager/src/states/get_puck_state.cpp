#include "../../include/states/get_puck_state.h"

GetPuckState::GetPuckState() : State(), timeIsUp(true), puckTouchTriggered(false),
                               lightDetected(false), leftTouchTriggered(false),
                               rightTouchTriggered(false), nextAction(SEARCH_RIGHT)
{
    SensorManager::getInstance()->subscribeToAll(this);
}

GetPuckState::~GetPuckState(){}

void GetPuckState::timeElapsedEventHandler()
{
    timeIsUp = true;
}

void GetPuckState::puckAquiredEventHandler()
{
    puckTouchTriggered = true;
}

void GetPuckState::puckLostEventHandler()
{
    puckTouchTriggered = false;
}

void GetPuckState::lightDetectedEventHandler()
{
    lightDetected = true;
}
void GetPuckState::lightLostEventHandler()
{
    lightDetected = false;
}

void GetPuckState::leftTouchTriggeredEventHandler()
{
    leftTouchTriggered = true;
}
void GetPuckState::leftTouchFreedEventHandler()
{
    leftTouchTriggered = false;
}

void GetPuckState::rightTouchTriggeredEventHandler()
{
    rightTouchTriggered = true;
}
void GetPuckState::rightTouchFreedEventHandler()
{
    rightTouchTriggered = false;
}

void GetPuckState::bothTouchTriggeredEventHandler()
{
    leftTouchTriggeredEventHandler();
    rightTouchTriggeredEventHandler();
}
void GetPuckState::bothTouchFreedEventHandler()
{
    leftTouchFreedEventHandler();
    rightTouchFreedEventHandler();
}

void GetPuckState::run()
{
    if (puckTouchTriggered)
    {
        ROS_INFO("Program - puck cached");
        MotorManager::getInstance()->publishCoords(0, 0);
        nextAction = SEARCH_LEFT;
        timeIsUp = true;
    }
    else if (leftTouchTriggered && rightTouchTriggered)
    {
        ROS_INFO("Program - front colision");
        MotorManager::getInstance()->publishCoords(-150, -150);
        nextAction = SEARCH_LEFT;
        timeIsUp = false;
        CallBackTimeManager::getInstance()->subscribe(this, 500000);
    }
    else if (leftTouchTriggered)
    {
        ROS_INFO("Program - left colision");
        MotorManager::getInstance()->publishCoords(-100, -150);
        nextAction = SEARCH_RIGHT;
        timeIsUp = false;
        CallBackTimeManager::getInstance()->subscribe(this, 500000);
    }
    else if (rightTouchTriggered)
    {
        ROS_INFO("Program - right colision");
        MotorManager::getInstance()->publishCoords(-150, -100);
        nextAction = SEARCH_LEFT;
        timeIsUp = false;
        CallBackTimeManager::getInstance()->subscribe(this, 500000);
    }
    else if (lightDetected)
    {
        ROS_INFO("Program - light detached");
        MotorManager::getInstance()->publishCoords(150, 150);
        nextAction = SEARCH_RIGHT;
        timeIsUp = true;
    }
    else if (timeIsUp)
    {
        ROS_INFO("Program - time is up");
        switch (nextAction)
        {
        case SEARCH_LEFT:
            MotorManager::getInstance()->publishCoords(0, 100);
            nextAction = MOVE_FORWARD;
            timeIsUp = false;
            CallBackTimeManager::getInstance()->subscribe(this, 1000000);
            break;
        case SEARCH_RIGHT:
            MotorManager::getInstance()->publishCoords(100, 0);
            nextAction = MOVE_FORWARD;
            timeIsUp = false;
            CallBackTimeManager::getInstance()->subscribe(this, 1000000);
            break;
        case MOVE_FORWARD:
            MotorManager::getInstance()->publishCoords(100, 100);
            nextAction = SEARCH_LEFT;
            timeIsUp = false;
            CallBackTimeManager::getInstance()->subscribe(this, 500000);
            break;
        }
    }
    ROS_INFO("Program - no action");
}