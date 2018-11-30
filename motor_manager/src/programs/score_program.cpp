#include "../../include/programs/score_program.h"

ScoreProgram::ScoreProgram(int irFrequency) : Program(), irFrequency(irFrequency)
{
    State *searchLeft = new SearchLeftState(this, SEARCHING_TIME);
    State *turnRight = new SearchRightState(this, TURN_TIME);
    State *moveForward = new MoveForwardState(this, MOVE_FORWARD_TIME);
    State *irDetected = new MoveForwardState(this);
    State *leftCollision = new MoveBackLeftState(this, COLLISION_TIME);
    State *rightCollision = new MoveBackRightState(this, COLLISION_TIME);
    State *bothCollision = new MoveBackwardState(this, COLLISION_TIME);

    searchLeft->setBothTouchTriggeredNextState(bothCollision)->setTimeElapsedNextState(moveForward);
    searchLeft->setRightTouchTriggeredNextState(rightCollision)->setLeftTouchTriggeredNextState(leftCollision);
    
    turnRight->setBothTouchTriggeredNextState(bothCollision)->setTimeElapsedNextState(searchLeft);
    turnRight->setRightTouchTriggeredNextState(rightCollision)->setLeftTouchTriggeredNextState(leftCollision);

    moveForward->setTimeElapsedNextState(searchLeft)->setBothTouchTriggeredNextState(bothCollision);
    moveForward->setRightTouchTriggeredNextState(rightCollision)->setLeftTouchTriggeredNextState(leftCollision);

    irDetected->setRightTouchTriggeredNextState(rightCollision)->setLeftTouchTriggeredNextState(leftCollision);
    irDetected->setBothTouchTriggeredNextState(bothCollision);

    leftCollision->setTimeElapsedNextState(searchLeft);
    rightCollision->setTimeElapsedNextState(searchLeft);
    bothCollision->setTimeElapsedNextState(searchLeft);

    if (irFrequency < 1000)
    {
        searchLeft->setIr600FoundNextState(irDetected);
        turnRight->setIr600FoundNextState(irDetected);
        moveForward->setIr600FoundNextState(irDetected);
        irDetected->setIr600LostNextState(turnRight);
    }
    else
    {
        searchLeft->setIr1500FoundNextState(irDetected);
        turnRight->setIr1500FoundNextState(irDetected);
        moveForward->setIr1500FoundNextState(irDetected);
        irDetected->setIr1500LostNextState(turnRight);
    }

    stateConut = 7;
    allStates = new State *[stateConut];
    allStates[0] = searchLeft;
    allStates[1] = moveForward;
    allStates[2] = irDetected;
    allStates[3] = leftCollision;
    allStates[4] = rightCollision;
    allStates[5] = bothCollision;
    allStates[6] = turnRight;

    actualState = nullptr;
    nextState = searchLeft;

    SensorManager::getInstance()->subscribePuckLostEvent(this);
}

ScoreProgram::~ScoreProgram()
{
    SensorManager::getInstance()->unsubscribeFromAll(this);
}

void ScoreProgram::puckLostEventHandler()
{
    ProgramManager::getInstance()->setProgram(new CatchPuckProgram(irFrequency));
}