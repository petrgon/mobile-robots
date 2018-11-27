#ifndef MOVE_BACKWARD_STATE_H
#define MOVE_BACKWARD_STATE_H

#include "state.h"
#include "../managers/motor_manager.h"

#define SPEED -100

class MoveBackwardState : public State
{
public:
  MoveBackwardState(Program *);
  MoveBackwardState(Program *, int);
  MoveBackwardState(const MoveBackwardState &) = default;
  MoveBackwardState(MoveBackwardState &&) = default;

  virtual ~MoveBackwardState() = 0;

  virtual MoveBackwardState &operator=(const MoveBackwardState &) = default;
  virtual MoveBackwardState &operator=(MoveBackwardState &&) = default;

  virtual bool operator==(const MoveBackwardState &b) const;

  virtual void run() override;
  virtual void stateInit() override;
};
#endif /*MOVE_BACKWARD_STATE_H*/