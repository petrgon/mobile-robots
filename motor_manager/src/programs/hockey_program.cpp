#include "../../include/programs/hockey_program.h"

HockeyProgram::HockeyProgram() : Program(), timeIsUp(true), puckTouchTriggered(false),
                               lightDetected(false), leftTouchTriggered(false),
                               rightTouchTriggered(false), actualAction(MOVE_FORWARD_LEFT)
{
    SensorManager::getInstance()->subscribeToAll(this);
}

HockeyProgram::~HockeyProgram() {}

void HockeyProgram::timeElapsedEventHandler()
{
    timeIsUp = true;
}

void HockeyProgram::puckAquiredEventHandler()
{
    puckTouchTriggered = true;
}

void HockeyProgram::puckLostEventHandler()
{
    puckTouchTriggered = false;
}

void HockeyProgram::lightDetectedEventHandler()
{
    lightDetected = true;
}
void HockeyProgram::lightLostEventHandler()
{
    lightDetected = false;
}

void HockeyProgram::leftTouchTriggeredEventHandler()
{
    leftTouchTriggered = true;
}
void HockeyProgram::leftTouchFreedEventHandler()
{
    leftTouchTriggered = false;
}

void HockeyProgram::rightTouchTriggeredEventHandler()
{
    rightTouchTriggered = true;
}
void HockeyProgram::rightTouchFreedEventHandler()
{
    rightTouchTriggered = false;
}

void HockeyProgram::bothTouchTriggeredEventHandler()
{
    leftTouchTriggeredEventHandler();
    rightTouchTriggeredEventHandler();
}
void HockeyProgram::bothTouchFreedEventHandler()
{
    leftTouchFreedEventHandler();
    rightTouchFreedEventHandler();
}

void HockeyProgram::run()
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

void HockeyProgram::doAction(int leftWheelSpeed, int rightWheelSpeed,
                            HockeyProgram::Actions nextAction, int timeOut)
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
