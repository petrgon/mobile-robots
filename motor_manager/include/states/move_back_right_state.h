#ifndef MOVE_MOVE_BACK_RIGHT_STATE_H
#define MOVE_MOVE_BACK_RIGHT_STATE_H

#include "state.h"
#include "../managers/motor_manager.h"

class MoveBackRightState : public State
{
public:
  MoveBackRightState(Program *);
  MoveBackRightState(Program *, int);
  MoveBackRightState(const MoveBackRightState &) = default;
  MoveBackRightState(MoveBackRightState &&) = default;

  virtual ~MoveBackRightState();

  virtual MoveBackRightState &operator=(const MoveBackRightState &) = default;
  virtual MoveBackRightState &operator=(MoveBackRightState &&) = default;

  virtual bool operator==(const MoveBackRightState &b) const;

  virtual void run() override;
  virtual void stateInit() override;

private:
  static const int SPEED_LEFT = -110;
  static const int SPEED_RIGHT = -90;
};
#endif /*MOVE_MOVE_BACK_RIGHT_STATE_H*/