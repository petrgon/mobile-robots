#include "../../include/programs/direct_search_puck_program.h"

DirectSearchPuckProgram::DirectSearchPuckProgram(int irFrequency) : Program(), irFrequency(irFrequency)
{
    State *dummyStartingState = new MoveState(this, 0, 0, 300);
    State *searchLeft = new SearchLeftState(this, SEARCHING_TIME);
    State *lookRight = new SearchRightState(this, ROTATION_TIME);
    State *turnRight = new SearchRightState(this, ROTATION_TIME);
    State *moveForward = new MoveForwardState(this, MOVE_FORWARD_TIME);
    State *catchLight = new MoveForwardState(this);
    State *leftCurve = new MoveState(this, CURVE_LEFT_SPEED, CURVE_RIGHT_SPEED, CURVE_TIME);
    State *endProgram = new ProgramTimeoutState(this);
    State *moveBack = new MoveBackwardState(this, COLLISION_TIME);
    State *unexpectedCollision = new MoveBackwardState(this, COLLISION_TIME);

    dummyStartingState->setTimeElapsedNextState(moveForward);

    moveForward->setCollisionNextState(moveBack)->setLightDetectedNextState(catchLight);
    moveForward->setTimeElapsedNextState(searchLeft);

    moveBack->setTimeElapsedNextState(turnRight);

    turnRight->setTimeElapsedNextState(leftCurve);

    leftCurve->setTimeElapsedNextState(lookRight)->setLightDetectedNextState(catchLight);
    leftCurve->setCollisionNextState(unexpectedCollision);

    catchLight->setLightLostNextState(lookRight);

    lookRight->setLightDetectedNextState(catchLight)->setTimeElapsedNextState(searchLeft);
    lookRight->setCollisionNextState(unexpectedCollision);

    searchLeft->setLightDetectedNextState(catchLight)->setCollisionNextState(unexpectedCollision);
    searchLeft->setTimeElapsedNextState(endProgram);

    unexpectedCollision->setTimeElapsedNextState(endProgram);

    stateConut = 9;
    allStates = new State *[stateConut];
    allStates[0] = searchLeft;
    allStates[1] = lookRight;
    allStates[2] = moveForward;
    allStates[3] = catchLight;
    allStates[4] = leftCurve;
    allStates[5] = endProgram;
    allStates[6] = moveBack;
    allStates[7] = unexpectedCollision;
    allStates[8] = dummyStartingState;

    actualState = nullptr;
    nextState = dummyStartingState;

    SensorManager::getInstance()->subscribePuckAquiredEvent(this);
}

DirectSearchPuckProgram::~DirectSearchPuckProgram()
{
    SensorManager::getInstance()->unsubscribeFromAll(this);
}

void DirectSearchPuckProgram::puckAquiredEventHandler()
{
    ProgramManager::getInstance()->setProgram(new ScoreProgram(irFrequency));
}

void DirectSearchPuckProgram::timeElapsedEventHandler()
{
    ProgramManager::getInstance()->setProgram(new CatchPuckProgram(irFrequency));
}