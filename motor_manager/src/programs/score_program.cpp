#include "../../include/programs/score_program.h"

ScoreProgram::ScoreProgram(int irFrequency) : Program(), irFrequency(irFrequency)
{
    State *searchLeft = new MoveState(this, -110, 130, SEARCHING_TIME);
    State *turnRight = new MoveState(this, 120, -110, TURN_TIME);
    State *moveForward = new MoveState(this, 120, 120, MOVE_FORWARD_TIME);
    State *irDetected = new MoveForwardState(this);
    State *moveBackLeft = new MoveState(this, -100, -120, MOVE_BACK_TIME);
    State *moveBackRight = new MoveState(this, -100, -120, MOVE_BACK_TIME);
    State *leftCollision = new MoveState(this, -100, -120, COLLISION_TIME);
    State *rightCollision = new MoveState(this, -120, -100, COLLISION_TIME);

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

    SensorManager::getInstance()->subscribeLightLostEvent(this);
}

ScoreProgram::~ScoreProgram()
{
    SensorManager::getInstance()->unsubscribeFromAll(this);
}

void ScoreProgram::lightLostEventHandler()
{
    ProgramManager::getInstance()->setProgram(new CatchPuckProgram(irFrequency));
}

std::string ScoreProgram::getName(){
    return "Score Program";
}
