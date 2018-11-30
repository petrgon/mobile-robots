#include "../../include/states/program_timeout_state.h"
#include "../../include/programs/program.h"

ProgramTimeoutState::ProgramTimeoutState(Program *program) : State(program) {}

ProgramTimeoutState::ProgramTimeoutState(Program *program, int timeOut) : State(program, timeOut) {}

ProgramTimeoutState::~ProgramTimeoutState(){}

void ProgramTimeoutState::stateInit() {
    State::stateInit();
    program->timeElapsedEventHandler();
}

