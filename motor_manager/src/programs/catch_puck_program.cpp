#include "../../include/programs/catch_puck_program.h"

CatchPuckProgram::CatchPuckProgram(int irFrequency) : Program(), irFrequency(irFrequency)
{
    State *searchLeft = new SearchLeftState(this, SEARCHING_TIME);
    State *searchRight = new SearchRightState(this, SEARCHING_TIME - 300);
    State *moveForwardLeft = new MoveForwardState(this, MOVE_FORWARD_TIME);
    State *moveForwardRight = new MoveForwardState(this, MOVE_FORWARD_TIME);
    State *lightDetected = new MoveForwardState(this);
    State *leftCollision = new MoveBackLeftState(this, COLLISION_TIME);
    State *rightCollision = new MoveBackRightState(this, COLLISION_TIME);
    State *bothCollision = new MoveBackwardState(this, COLLISION_TIME);

    leftCollision->setTimeElapsedNextState(searchRight);
    rightCollision->setTimeElapsedNextState(searchLeft);
    bothCollision->setTimeElapsedNextState(searchRight);

    searchLeft->setTimeElapsedNextState(moveForwardRight)->setBothTouchTriggeredNextState(bothCollision);
    searchLeft->setRightTouchTriggeredNextState(rightCollision)->setLeftTouchTriggeredNextState(leftCollision);
    searchLeft->setLightDetectedNextState(lightDetected);

    searchRight->setTimeElapsedNextState(moveForwardLeft)->setBothTouchTriggeredNextState(bothCollision);
    searchRight->setRightTouchTriggeredNextState(rightCollision)->setLeftTouchTriggeredNextState(leftCollision);
    searchRight->setLightDetectedNextState(lightDetected);

    moveForwardLeft->setTimeElapsedNextState(searchLeft)->setBothTouchTriggeredNextState(bothCollision);
    moveForwardLeft->setRightTouchTriggeredNextState(rightCollision)->setLeftTouchTriggeredNextState(leftCollision);
    moveForwardLeft->setLightDetectedNextState(lightDetected);

    moveForwardRight->setTimeElapsedNextState(searchRight)->setBothTouchTriggeredNextState(bothCollision);
    moveForwardRight->setRightTouchTriggeredNextState(rightCollision)->setLeftTouchTriggeredNextState(leftCollision);
    moveForwardRight->setLightDetectedNextState(lightDetected);

    lightDetected->setRightTouchTriggeredNextState(rightCollision)->setLeftTouchTriggeredNextState(leftCollision);
    lightDetected->setBothTouchTriggeredNextState(bothCollision)->setLightLostNextState(searchLeft);

    stateConut = 8;
    allStates = new State *[stateConut];
    allStates[0] = searchLeft;
    allStates[1] = searchRight;
    allStates[2] = moveForwardLeft;
    allStates[3] = moveForwardRight;
    allStates[4] = lightDetected;
    allStates[5] = leftCollision;
    allStates[6] = rightCollision;
    allStates[7] = bothCollision;

    actualState = nullptr;
    nextState = moveForwardRight;

    SensorManager::getInstance()->subscribePuckAquiredEvent(this);
}

CatchPuckProgram::~CatchPuckProgram()
{
    SensorManager::getInstance()->unsubscribeFromAll(this);
}

void CatchPuckProgram::puckAquiredEventHandler()
{
    ProgramManager::getInstance()->setProgram(new ScoreProgram(irFrequency));
}

std::string CatchPuckProgram::getName(){
    return "Catch Puck Program";
}
