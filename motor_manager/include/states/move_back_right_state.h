#ifndef MOVE_MOVE_BACK_RIGHT_STATE_H
#define MOVE_MOVE_BACK_RIGHT_STATE_H

#include "state.h"
#include "../managers/motor_manager.h"

#define SPEED_LEFT -110
#define SPEED_RIGHT -90

class MoveBackRightState : public State
{
public:
  MoveBackRightState(Program *);
  MoveBackRightState(Program *, int);
  MoveBackRightState(const MoveBackRightState &) = default;
  MoveBackRightState(MoveBackRightState &&) = default;

  virtual ~MoveBackRightState() = 0;

  virtual MoveBackRightState &operator=(const MoveBackRightState &) = default;
  virtual MoveBackRightState &operator=(MoveBackRightState &&) = default;

  virtual bool operator==(const MoveBackRightState &b) const;

  virtual void run() override;
  virtual void stateInit() override;
};
#endif /*MOVE_MOVE_BACK_RIGHT_STATE_H*/