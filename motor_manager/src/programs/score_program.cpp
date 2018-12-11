#include "../../include/programs/score_program.h"

ScoreProgram::ScoreProgram(int irFrequency) : Program(), irFrequency(irFrequency)
{
    State *searchLeft = new MoveState(this, -110, 130, SEARCHING_TIME);
    State *turnRight = new MoveState(this, 120, -110, TURN_TIME);
    State *moveForward = new MoveState(this, 120, 120, MOVE_FORWARD_TIME);
    State *irDetected = new MoveForwardState(this);
    State *moveBackLeftColl = new MoveBackwardState(this, MOVE_BACK_TIME);
    State *moveBackRightColl = new MoveBackwardState(this, MOVE_BACK_TIME);
    State *moveBackBothColl = new MoveBackwardState(this, MOVE_BACK_TIME);
    State *leftCollision = new SearchLeftState(this, COLLISION_TIME);
    State *rightCollision = new SearchRightState(this, COLLISION_TIME);
    State *bothCollision = new RotateLeftRightState(this, COLLISION_TIME);

    searchLeft->setBothTouchTriggeredNextState(moveBackBothColl)->setTimeElapsedNextState(moveForward);
    searchLeft->setRightTouchTriggeredNextState(moveBackRightColl)->setLeftTouchTriggeredNextState(moveBackLeftColl);
    
    turnRight->setBothTouchTriggeredNextState(moveBackBothColl)->setTimeElapsedNextState(searchLeft);
    turnRight->setRightTouchTriggeredNextState(moveBackRightColl)->setLeftTouchTriggeredNextState(moveBackLeftColl);

    moveForward->setTimeElapsedNextState(searchLeft)->setBothTouchTriggeredNextState(moveBackBothColl);
    moveForward->setRightTouchTriggeredNextState(moveBackRightColl)->setLeftTouchTriggeredNextState(moveBackLeftColl);

    irDetected->setRightTouchTriggeredNextState(moveBackRightColl)->setLeftTouchTriggeredNextState(leftCollision);
    irDetected->setBothTouchTriggeredNextState(moveBackBothColl);

    moveBackLeftColl->setTimeElapsedNextState(leftCollision);
    moveBackRightColl->setTimeElapsedNextState(rightCollision);
    moveBackBothColl->setTimeElapsedNextState(bothCollision);
    
    leftCollision->setRightTouchTriggeredNextState(moveBackRightColl)->setLeftTouchTriggeredNextState(moveBackLeftColl);
    leftCollision->setBothTouchTriggeredNextState(moveBackBothColl);
    
    rightCollision->setRightTouchTriggeredNextState(moveBackRightColl)->setLeftTouchTriggeredNextState(moveBackLeftColl);
    rightCollision->setBothTouchTriggeredNextState(moveBackBothColl);
    
    bothCollision->setRightTouchTriggeredNextState(moveBackRightColl)->setLeftTouchTriggeredNextState(moveBackLeftColl);
    bothCollision->setBothTouchTriggeredNextState(moveBackBothColl);
    
    leftCollision->setTimeElapsedNextState(moveForward);
    rightCollision->setTimeElapsedNextState(moveForward);
    bothCollision->setTimeElapsedNextState(moveForward);

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

    stateConut = 10;
    allStates = new State *[stateConut];
    allStates[0] = searchLeft;
    allStates[1] = moveForward;
    allStates[2] = irDetected;
    allStates[3] = leftCollision;
    allStates[4] = rightCollision;
    allStates[5] = bothCollision;
    allStates[6] = turnRight;
    allStates[7] = moveBackLeftColl;
    allStates[8] = moveBackRightColl;
    allStates[9] = moveBackBothColl;

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
