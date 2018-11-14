#include "../../include/states/get_puck_state.h"

GetPuckState::GetPuckState() : State(), timeIsUp(true), puckTouchTriggered(false),
                               lightDetected(false), leftTouchTriggered(false),
                               rightTouchTriggered(false), actualAction(MOVE_FORWARD)
{
    SensorManager::getInstance()->subscribeToAll(this);
}

GetPuckState::~GetPuckState() {}

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
        if (actualAction != PUCK_TRIGGERED)
        {
            ROS_INFO("Program - puck cached");
            MotorManager::getInstance()->publishCoords(0, 0);
            actualAction = PUCK_TRIGGERED;
            timeIsUp = true;
        }
    }
    else if (leftTouchTriggered && rightTouchTriggered)
    {
        if (actualAction != BOTH_TRIGGERED)
        {
            ROS_INFO("Program - front colision");
            MotorManager::getInstance()->publishCoords(-120, -120);
            actualAction = BOTH_TRIGGERED;
            timeIsUp = false;
            CallBackTimeManager::getInstance()->subscribe(this, 500);
        }
    }
    else if (leftTouchTriggered)
    {
        if (actualAction != LEFT_TRIGGERED)
        {
            ROS_INFO("Program - left colision");
            MotorManager::getInstance()->publishCoords(-100, -120);
            actualAction = LEFT_TRIGGERED;
            timeIsUp = false;
            CallBackTimeManager::getInstance()->subscribe(this, 500);
        }
    }
    else if (rightTouchTriggered)
    {
        if (actualAction != RIGHT_TRIGGERED)
        {
            ROS_INFO("Program - right colision");
            MotorManager::getInstance()->publishCoords(-120, -100);
            actualAction = RIGHT_TRIGGERED;
            timeIsUp = false;
            CallBackTimeManager::getInstance()->subscribe(this, 500);
        }
    }
    else if (lightDetected)
    {
        if (actualAction != LIGHT_DETECTED)
        {
            ROS_INFO("Program - light detached");
            MotorManager::getInstance()->publishCoords(100, 100);
            actualAction = LIGHT_DETECTED;
            timeIsUp = true;
        }
    }
    else if (timeIsUp)
    {
        ROS_INFO("Program - time is up");
        switch (actualAction)
        {
        case MOVE_FORWARD:
        case PUCK_TRIGGERED:
        case RIGHT_TRIGGERED:
            MotorManager::getInstance()->publishCoords(-95, 95);
            actualAction = SEARCH_LEFT;
            timeIsUp = false;
            CallBackTimeManager::getInstance()->subscribe(this, 2300);
            break;
        case LEFT_TRIGGERED:
        case LIGHT_DETECTED:
        case BOTH_TRIGGERED:
            MotorManager::getInstance()->publishCoords(100, -100);
            actualAction = SEARCH_RIGHT;
            timeIsUp = false;
            CallBackTimeManager::getInstance()->subscribe(this, 2300);
            break;
        case SEARCH_LEFT:
        case SEARCH_RIGHT:
            MotorManager::getInstance()->publishCoords(100, 100);
            actualAction = MOVE_FORWARD;
            timeIsUp = false;
            CallBackTimeManager::getInstance()->subscribe(this, 1500);
            break;
        }
    }
}
