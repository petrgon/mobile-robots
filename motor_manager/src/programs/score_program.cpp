#include "../../include/programs/score_program.h"

ScoreProgram::ScoreProgram(int irFrequency) : Program(), irFrequency(irFrequency)
{
    State *search = new SearchLeftState(this, SEARCHING_TIME);
    State *moveForward = new MoveForwardState(this, MOVE_FORWARD_TIME);
    State *irDetected = new MoveForwardState(this);
    State *leftCollision = new MoveBackLeftState(this, COLLISION_TIME);
    State *rightCollision = new MoveBackRightState(this, COLLISION_TIME);
    State *bothCollision = new MoveBackwardState(this, COLLISION_TIME);

    search->setBothTouchTriggeredNextState(bothCollision)->setTimeElapsedNextState(moveForward);
    search->setRightTouchTriggeredNextState(rightCollision)->setLeftTouchTriggeredNextState(leftCollision);

    moveForward->setTimeElapsedNextState(search)->setBothTouchTriggeredNextState(bothCollision);
    moveForward->setRightTouchTriggeredNextState(rightCollision)->setLeftTouchTriggeredNextState(leftCollision);

    irDetected->setRightTouchTriggeredNextState(rightCollision)->setLeftTouchTriggeredNextState(leftCollision);
    irDetected->setBothTouchTriggeredNextState(bothCollision);

    leftCollision->setTimeElapsedNextState(search);
    rightCollision->setTimeElapsedNextState(search);
    bothCollision->setTimeElapsedNextState(search);
    
    if (irFrequency < 1000){
        search->setIr600FoundNextState(irDetected);
        moveForward->setIr600FoundNextState(irDetected);
        irDetected->setIr600LostNextState(search);
    } else {
        search->setIr1500FoundNextState(irDetected);
        moveForward->setIr1500FoundNextState(irDetected);
        irDetected->setIr1500LostNextState(search);
    }

    stateConut = 6;
    allStates = new State*[stateConut];
    allStates[0] = search;
    allStates[1] = moveForward;
    allStates[2] = irDetected;
    allStates[3] = leftCollision;
    allStates[4] = rightCollision;
    allStates[5] = bothCollision;

    actualState = nullptr;
    nextState = search;

    SensorManager::getInstance()->subscribePuckLostEvent(this);
}

ScoreProgram::~ScoreProgram(){}

void ScoreProgram::puckLostEventHandler(){
    ProgramManager::getInstance()->setProgram(new CatchPuckProgram(irFrequency));
}