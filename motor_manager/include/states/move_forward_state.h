#ifndef MOVE_FORWARD_STATE_H
#define MOVE_FORWARD_STATE_H

#include "move_state.h"
#include "../managers/motor_manager.h"

class MoveForwardState : public MoveState
{
public:
  MoveForwardState(Program *);
  MoveForwardState(Program *, int);
  MoveForwardState(const MoveForwardState &) = default;
  MoveForwardState(MoveForwardState &&) = default;

  virtual ~MoveForwardState() override;

  virtual MoveForwardState &operator=(const MoveForwardState &) = default;
  virtual MoveForwardState &operator=(MoveForwardState &&) = default;

private:
  static const int SPEED = 100;
};
#endif /*MOVE_FORWARD_STATE_H*/