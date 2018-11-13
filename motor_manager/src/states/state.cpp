#include "../../include/states/state.h"
State::State() {}

State::~State() {}

bool State::operator==(const State & b) const {
    return this == &b;
}

void State::timeElapsedEventHandler() {}

void State::puckAquiredEventHandler() {}

void State::lightDetectedEventHandler() {}
void State::lightLostEventHandler() {}

void State::leftTouchTriggeredEventHandler() {}
void State::leftTouchFreedEventHandler() {}

void State::rightTouchTriggeredEventHandler() {}
void State::rightTouchFreedEventHandler() {}

void State::bothTouchTriggeredEventHandler() {}
void State::bothtTouchFreedEventHandler() {}