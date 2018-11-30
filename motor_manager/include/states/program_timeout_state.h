#ifndef PROGRAM_TIMEOUT_STATE_H
#define PROGRAM_TIMEOUT_STATE_H

#include "state.h"
#include "../managers/motor_manager.h"

class ProgramTimeoutState : public State
{
public:
  ProgramTimeoutState(Program *);
  ProgramTimeoutState(Program *, int);
  ProgramTimeoutState(const ProgramTimeoutState &) = default;
  ProgramTimeoutState(ProgramTimeoutState &&) = default;

  virtual ~ProgramTimeoutState() override;

  virtual ProgramTimeoutState &operator=(const ProgramTimeoutState &) = default;
  virtual ProgramTimeoutState &operator=(ProgramTimeoutState &&) = default;

  virtual void stateInit() override;
};
#endif /*PROGRAM_TIMEOUT_STATE_H*/