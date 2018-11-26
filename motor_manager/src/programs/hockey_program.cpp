#include "../../include/programs/get_puck_program.h"

GetPuckProgram::GetPuckProgram() : Program(), timeIsUp(true), puckTouchTriggered(false),
                               lightDetected(false), leftTouchTriggered(false),
                               rightTouchTriggered(false), actualAction(MOVE_FORWARD_LEFT)
{
    SensorManager::getInstance()->subscribeToAll(this);
}

GetPuckProgram::~GetPuckProgram() {}

void GetPuckProgram::timeElapsedEventHandler()
{
    timeIsUp = true;
}

void GetPuckProgram::puckAquiredEventHandler()
{
    puckTouchTriggered = true;
}

void GetPuckProgram::puckLostEventHandler()
{
    puckTouchTriggered = false;
}

void GetPuckProgram::lightDetectedEventHandler()
{
    lightDetected = true;
}
void GetPuckProgram::lightLostEventHandler()
{
    lightDetected = false;
}

void GetPuckProgram::leftTouchTriggeredEventHandler()
{
    leftTouchTriggered = true;
}
void GetPuckProgram::leftTouchFreedEventHandler()
{
    leftTouchTriggered = false;
}

void GetPuckProgram::rightTouchTriggeredEventHandler()
{
    rightTouchTriggered = true;
}
void GetPuckProgram::rightTouchFreedEventHandler()
{
    rightTouchTriggered = false;
}

void GetPuckProgram::bothTouchTriggeredEventHandler()
{
    leftTouchTriggeredEventHandler();
    rightTouchTriggeredEventHandler();
}
void GetPuckProgram::bothTouchFreedEventHandler()
{
    leftTouchFreedEventHandler();
    rightTouchFreedEventHandler();
}

void GetPuckProgram::run()
{
    if (puckTouchTriggered)
    {
        if (actualAction != PUCK_TRIGGERED)
        {
            doAction(0, 0, PUCK_TRIGGERED, -1);
        }
    }
    else if (leftTouchTriggered && rightTouchTriggered)
    {
        if (actualAction != BOTH_TRIGGERED)
        {
            doAction(-100, -100, BOTH_TRIGGERED, 450);
        }
    }
    else if (leftTouchTriggered)
    {
        if (actualAction != LEFT_TRIGGERED)
        {
            doAction(-90, -110, LEFT_TRIGGERED, 450);
        }
    }
    else if (rightTouchTriggered)
    {
        if (actualAction != RIGHT_TRIGGERED)
        {
            doAction(-110, -90, RIGHT_TRIGGERED, 450);
        }
    }
    else if (lightDetected)
    {
        if (actualAction != LIGHT_DETECTED)
        {
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
            doAction(-95, 100, SEARCH_LEFT, 3000);
            break;
        case LEFT_TRIGGERED:
        case MOVE_FORWARD_RIGHT:
        case LIGHT_DETECTED:
        case BOTH_TRIGGERED:
            doAction(100, -95, SEARCH_RIGHT, 3000);
            break;
        case SEARCH_LEFT:
            doAction(100, 100, MOVE_FORWARD_RIGHT, 2000);
            break;

        case SEARCH_RIGHT:
            doAction(100, 100, MOVE_FORWARD_LEFT, 2000);
            break;
        }
    }
}

void GetPuckProgram::doAction(int leftWheelSpeed, int rightWheelSpeed,
                            GetPuckProgram::Actions nextAction, int timeOut)
{
    MotorManager::getInstance()->publishCoords(leftWheelSpeed, rightWheelSpeed);
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
