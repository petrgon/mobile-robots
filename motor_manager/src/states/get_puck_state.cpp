#include "../../include/states/get_puck_state.h"

GetPuckState::GetPuckState() : State(), timeIsUp(true), puckTouchTriggered(false),
                               lightDetected(false), leftTouchTriggered(false),
                               rightTouchTriggered(false), actualAction(MOVE_FORWARD_LEFT)
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
            doAction(0, 0, PUCK_TRIGGERED, -1);
        }
    }
    else if (leftTouchTriggered && rightTouchTriggered)
    {
        if (actualAction != BOTH_TRIGGERED)
        {
            ROS_INFO("Program - front colision");
            doAction(-120, -120, BOTH_TRIGGERED, 750);
        }
    }
    else if (leftTouchTriggered)
    {
        if (actualAction != LEFT_TRIGGERED)
        {
            ROS_INFO("Program - left colision");
            doAction(-100, -120, LEFT_TRIGGERED, 750);
        }
    }
    else if (rightTouchTriggered)
    {
        if (actualAction != RIGHT_TRIGGERED)
        {
            ROS_INFO("Program - right colision");
            doAction(-120, -100, RIGHT_TRIGGERED, 750);
        }
    }
    else if (lightDetected)
    {
        if (actualAction != LIGHT_DETECTED)
        {
            ROS_INFO("Program - light detached");
            doAction(100, 100, LIGHT_DETECTED, -1);
        }
    }
    else if (timeIsUp)
    {
        switch (actualAction)
        {
        case MOVE_FORWARD_LEFT:
        case PUCK_TRIGGERED:
        case RIGHT_TRIGGERED:
            doAction(-95, 95, SEARCH_LEFT, 2300);
            break;
        case LEFT_TRIGGERED:
        case MOVE_FORWARD_RIGHT:
        case LIGHT_DETECTED:
        case BOTH_TRIGGERED:
            doAction(100, -100, SEARCH_RIGHT, 2300);
            break;
        case SEARCH_LEFT:
            doAction(100, 100, MOVE_FORWARD_RIGHT, 1500);
            break;
        case SEARCH_RIGHT:
            doAction(100, 100, MOVE_FORWARD_LEFT, 1500);
            break;
        }
    }
}

void GetPuckState::doAction(int leftWheelSpeed, int rightWheelSpeed,
                            GetPuckState::Actions nextAction, int timeOut)
{
    MotorManager::getInstance()->publishCoords(leftWheelSpeed, leftWheelSpeed);
    actualAction = nextAction;
    if (timeOut > 0)
    {
        timeIsUp = false;
        CallBackTimeManager::getInstance()->subscribe(this, timeOut);
    }
    else
    {
        timeIsUp = true;
    }
}