#include "../../include/programs/direct_search_puck_program.h"

DirectSearchPuckProgram::DirectSearchPuckProgram(int irFrequency) : Program(), irFrequency(irFrequency)
{
    State *lookRight = new SearchRightState(this, ROTATION_TIME);
    State *turnRight = new MoveState(this, 150, 0, ROTATION_TIME);
    State *moveForward = new MoveForwardState(this, MOVE_FORWARD_TIME);
    State *catchLight = new MoveForwardState(this);
    State *leftCurve = new MoveState(this, CURVE_LEFT_SPEED, CURVE_RIGHT_SPEED, CURVE_TIME);
    State *endProgram = new ProgramTimeoutState(this);
    State *moveBack = new MoveBackwardState(this, COLLISION_TIME);
    State *unexpectedCollision = new MoveBackwardState(this, COLLISION_TIME);

    moveForward->setCollisionNextState(moveBack)->setLightDetectedNextState(catchLight);
    moveForward->setTimeElapsedNextState(endProgram);

    moveBack->setTimeElapsedNextState(turnRight);

    turnRight->setTimeElapsedNextState(leftCurve);

    leftCurve->setTimeElapsedNextState(lookRight)->setLightDetectedNextState(catchLight);
    leftCurve->setCollisionNextState(unexpectedCollision);

    catchLight->setLightLostNextState(lookRight);

    lookRight->setLightDetectedNextState(catchLight)->setTimeElapsedNextState(endProgram);
    lookRight->setCollisionNextState(unexpectedCollision);

    unexpectedCollision->setTimeElapsedNextState(endProgram);

    stateConut = 7;
    allStates = new State *[stateConut];
    allStates[0] = unexpectedCollision;
    allStates[1] = lookRight;
    allStates[2] = moveForward;
    allStates[3] = catchLight;
    allStates[4] = leftCurve;
    allStates[5] = endProgram;
    allStates[6] = moveBack;

    actualState = nullptr;
    nextState = moveForward;

    SensorManager::getInstance()->subscribePuckAquiredEvent(this);
}

DirectSearchPuckProgram::DirectSearchPuckProgram(int irFrequency, int leftSpeed, int rightSpeed, int time)
    : Program(), irFrequency(irFrequency) {
        
    State *startingMove = new MoveState(this, leftSpeed, rightSpeed, time);
    
    State *lookRight = new SearchRightState(this, ROTATION_TIME);
    State *catchLight = new MoveState(this, 150, 165);
    State *endProgram = new ProgramTimeoutState(this);
    State *unexpectedCollision = new MoveBackwardState(this, COLLISION_TIME);

    startingMove->setCollisionNextState(unexpectedCollision)->setLightDetectedNextState(catchLight);
    startingMove->setTimeElapsedNextState(endProgram);

    catchLight->setLightLostNextState(lookRight);

    lookRight->setLightDetectedNextState(catchLight)->setTimeElapsedNextState(endProgram);
    lookRight->setCollisionNextState(unexpectedCollision);

    unexpectedCollision->setTimeElapsedNextState(endProgram);

    stateConut = 5;
    allStates = new State *[stateConut];
    allStates[0] = lookRight;
    allStates[1] = startingMove;
    allStates[2] = catchLight;
    allStates[3] = endProgram;
    allStates[4] = unexpectedCollision;

    actualState = nullptr;
    nextState = startingMove;

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

std::string DirectSearchPuckProgram::getName()
{
    return "Direct Search Puck Program";
}
