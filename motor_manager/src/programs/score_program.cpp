#include "../../include/programs/score_program.h"

ScoreProgram::ScoreProgram(int irFrequency) : Program(), irFrequency(irFrequency)
{
    State *searchLeft = new MoveState(this, -100, 110, SEARCHING_TIME);
    State *turnRight = new MoveState(this, 110, -100, TURN_TIME);
    State *moveForward = new MoveState(this, 115, 115, MOVE_FORWARD_TIME);
    State *irDetected = new MoveForwardState(this);
    State *leftCollision = new MoveState(this, 0, -120, COLLISION_TIME);
    State *rightCollision = new MoveState(this, -120, 0, COLLISION_TIME);
    State *bothCollision = new RotateLeftRightState(this, COLLISION_TIME);

    searchLeft->setBothTouchTriggeredNextState(bothCollision)->setTimeElapsedNextState(moveForward);
    searchLeft->setRightTouchTriggeredNextState(rightCollision)->setLeftTouchTriggeredNextState(leftCollision);
    
    turnRight->setBothTouchTriggeredNextState(bothCollision)->setTimeElapsedNextState(searchLeft);
    turnRight->setRightTouchTriggeredNextState(rightCollision)->setLeftTouchTriggeredNextState(leftCollision);

    moveForward->setTimeElapsedNextState(searchLeft)->setBothTouchTriggeredNextState(bothCollision);
    moveForward->setRightTouchTriggeredNextState(rightCollision)->setLeftTouchTriggeredNextState(leftCollision);

    irDetected->setRightTouchTriggeredNextState(bothCollision)->setLeftTouchTriggeredNextState(leftCollision);
    irDetected->setBothTouchTriggeredNextState(rightCollision);
    
    leftCollision->setTimeElapsedNextState(moveForward);
    rightCollision->setTimeElapsedNextState(moveForward);
    bothCollision->setTimeElapsedNextState(moveForward);

    if (irFrequency < 1000)
    {
        searchLeft->setIr600FoundNextState(irDetected);
        turnRight->setIr600FoundNextState(irDetected);
        moveForward->setIr600FoundNextState(irDetected);
        irDetected->setIr600LostNextState(turnRight);
        leftCollision->setIr600FoundNextState(irDetected);
        rightCollision->setIr600FoundNextState(irDetected);
        bothCollision->setIr600FoundNextState(irDetected);
    }
    else
    {
        searchLeft->setIr1500FoundNextState(irDetected);
        turnRight->setIr1500FoundNextState(irDetected);
        moveForward->setIr1500FoundNextState(irDetected);
        irDetected->setIr1500LostNextState(turnRight);
        leftCollision->setIr1500FoundNextState(irDetected);
        rightCollision->setIr1500FoundNextState(irDetected);
        bothCollision->setIr1500FoundNextState(irDetected);
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
