#include "../../include/states/state.h"
State::State() {}

State::~State() {}

bool State::operator==(const State &b) const
{
    return this == &b;
}

void State::timeElapsedEventHandler() {}

void State::puckAquiredEventHandler() {}
void State::puckLostEventHandler() {}

void State::lightDetectedEventHandler() {}
void State::lightLostEventHandler() {}

void State::leftTouchTriggeredEventHandler() {}
void State::leftTouchFreedEventHandler() {}

void State::rightTouchTriggeredEventHandler() {}
void State::rightTouchFreedEventHandler() {}

void State::bothTouchTriggeredEventHandler() {}
void State::bothTouchFreedEventHandler() {}

void State::ir600FoundEventHandler() {}
void State::ir600LostEventHandler() {}

void State::ir1500FoundEventHandler() {}
void State::ir1500LostEventHandler() {}