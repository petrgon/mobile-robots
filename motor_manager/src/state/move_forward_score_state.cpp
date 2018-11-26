#include "../../include/states/move_forward_score_state.h"

MoveForwardScoreState::MoveForwardScoreState(Program *program) : MoveForwardState(program){}

void MoveForwardScoreState::timeElapsedEventHandler() {
    program->changeState(ScoreProgramStates::SEARCH_LEFT);
}

//TODO add logic
void MoveForwardScoreState::puckAquiredEventHandler() {}
void MoveForwardScoreState::puckLostEventHandler() {}

void MoveForwardScoreState::lightDetectedEventHandler() {}
void MoveForwardScoreState::lightLostEventHandler() {}

void MoveForwardScoreState::leftTouchTriggeredEventHandler() {}
void MoveForwardScoreState::leftTouchFreedEventHandler() {}

void MoveForwardScoreState::rightTouchTriggeredEventHandler() {}
void MoveForwardScoreState::rightTouchFreedEventHandler() {}

void MoveForwardScoreState::bothTouchTriggeredEventHandler() {}
void MoveForwardScoreState::bothTouchFreedEventHandler() {}

void MoveForwardScoreState::ir600FoundEventHandler() {}
void MoveForwardScoreState::ir600LostEventHandler() {}

void MoveForwardScoreState::ir1500FoundEventHandler() {}
void MoveForwardScoreState::ir1500LostEventHandler() {}