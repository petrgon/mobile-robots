#ifndef MOVE_STATE_H
#define MOVE_STATE_H

#include "state.h"
#include "../managers/motor_manager.h"

class MoveState : public State
{
public:
  MoveState(Program *, int, int);
  MoveState(Program *, int, int, int);
  MoveState(const MoveState &) = default;
  MoveState(MoveState &&) = default;

  virtual ~MoveState() override;

  virtual MoveState &operator=(const MoveState &) = default;
  virtual MoveState &operator=(MoveState &&) = default;

  virtual void stateInit() override;

  private:
    int leftWheelSpeed;
    int rightWheelSpeed;
};
#endif /*MOVE_STATE_H*/