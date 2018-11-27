#ifndef MOVE_FORWARD_STATE_H
#define MOVE_FORWARD_STATE_H

#include "state.h"
#include "../managers/motor_manager.h"

class MoveForwardState : public State
{
public:
  MoveForwardState(Program *);
  MoveForwardState(Program *, int);
  MoveForwardState(const MoveForwardState &) = default;
  MoveForwardState(MoveForwardState &&) = default;

  virtual ~MoveForwardState();

  virtual MoveForwardState &operator=(const MoveForwardState &) = default;
  virtual MoveForwardState &operator=(MoveForwardState &&) = default;

  virtual bool operator==(const MoveForwardState &b) const;

  virtual void run() override;
  virtual void stateInit() override;

private:
  static const int SPEED = 100;
};
#endif /*MOVE_FORWARD_STATE_H*/