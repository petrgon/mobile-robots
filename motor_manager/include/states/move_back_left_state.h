#ifndef MOVE_MOVE_BACK_LEFT_STATE_H
#define MOVE_MOVE_BACK_LEFT_STATE_H

#include "state.h"
#include "../managers/motor_manager.h"

class MoveBackLeftState : public State
{
public:
  MoveBackLeftState(Program *);
  MoveBackLeftState(Program *, int);
  MoveBackLeftState(const MoveBackLeftState &) = default;
  MoveBackLeftState(MoveBackLeftState &&) = default;

  virtual ~MoveBackLeftState() override;

  virtual MoveBackLeftState &operator=(const MoveBackLeftState &) = default;
  virtual MoveBackLeftState &operator=(MoveBackLeftState &&) = default;

  virtual void stateInit() override;

private:
  static const int SPEED_LEFT = -90;
  static const int SPEED_RIGHT = -110;
};
#endif /*MOVE_MOVE_BACK_LEFT_STATE_H*/