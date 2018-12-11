#ifndef ROTATE_LEFT_RIGHT_STATE_H
#define ROTATE_LEFT_RIGHT_STATE_H

#include "move_state.h"
#include "../managers/motor_manager.h"

class RotateLeftRightState : public MoveState
{
public:
  RotateLeftRightState(Program *);
  RotateLeftRightState(Program *, int);
  RotateLeftRightState(const RotateLeftRightState &) = default;
  RotateLeftRightState(RotateLeftRightState &&) = default;
  
  virtual ~RotateLeftRightState() override;

  virtual RotateLeftRightState &operator=(const RotateLeftRightState &) = default;
  virtual RotateLeftRightState &operator=(RotateLeftRightState &&) = default;

  virtual void stateInit() override;

private:
  static const int SPEED_A = -85;
  static const int SPEED_B = 95;

  bool speedALeft;
};
#endif /*ROTATE_LEFT_RIGHT_STATE_H*/
