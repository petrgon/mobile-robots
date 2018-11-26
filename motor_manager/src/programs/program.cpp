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

void Program::ir600FoundEventHandler() {}
void Program::ir600LostEventHandler() {}

void Program::ir1500FoundEventHandler() {}
void Program::ir1500LostEventHandler() {}