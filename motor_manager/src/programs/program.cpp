#include "../../include/programs/program.h"

Program::Program() {}

Program::~Program() {}

bool Program::operator==(const Program &b) const
{
    return this == &b;
}

void Program::timeElapsedEventHandler() {}

void Program::puckAquiredEventHandler() {}
void Program::puckLostEventHandler() {}

void Program::lightDetectedEventHandler() {}
void Program::lightLostEventHandler() {}

void Program::leftTouchTriggeredEventHandler() {}
void Program::leftTouchFreedEventHandler() {}

void Program::rightTouchTriggeredEventHandler() {}
void Program::rightTouchFreedEventHandler() {}

void Program::bothTouchTriggeredEventHandler() {}
void Program::bothTouchFreedEventHandler() {}