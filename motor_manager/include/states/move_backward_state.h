#ifndef MOVE_BACKWARD_STATE_H
#define MOVE_BACKWARD_STATE_H

#include "move_state.h"
#include "../managers/motor_manager.h"

class MoveBackwardState : public MoveState
{
public:
  MoveBackwardState(Program *);
  MoveBackwardState(Program *, int);
  MoveBackwardState(const MoveBackwardState &) = default;
  MoveBackwardState(MoveBackwardState &&) = default;

  virtual ~MoveBackwardState() override;

  virtual MoveBackwardState &operator=(const MoveBackwardState &) = default;
  virtual MoveBackwardState &operator=(MoveBackwardState &&) = default;

private:
  static const int SPEED = -110;
};
#endif /*MOVE_BACKWARD_STATE_H*/