#ifndef MOVE_MOVE_BACK_RIGHT_STATE_H
#define MOVE_MOVE_BACK_RIGHT_STATE_H

#include "move_state.h"
#include "../managers/motor_manager.h"

class MoveBackRightState : public MoveState
{
public:
  MoveBackRightState(Program *);
  MoveBackRightState(Program *, int);
  MoveBackRightState(const MoveBackRightState &) = default;
  MoveBackRightState(MoveBackRightState &&) = default;

  virtual ~MoveBackRightState() override;

  virtual MoveBackRightState &operator=(const MoveBackRightState &) = default;
  virtual MoveBackRightState &operator=(MoveBackRightState &&) = default;

private:
  static const int SPEED_LEFT = -110;
  static const int SPEED_RIGHT = -90;
};
#endif /*MOVE_MOVE_BACK_RIGHT_STATE_H*/