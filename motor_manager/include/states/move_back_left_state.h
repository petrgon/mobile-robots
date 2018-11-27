#ifndef MOVE_MOVE_BACK_LEFT_STATE_H
#define MOVE_MOVE_BACK_LEFT_STATE_H

#include "state.h"
#include "../managers/motor_manager.h"

#define SPEED_LEFT -90
#define SPEED_RIGHT -110

class MoveBackLeftState : public State
{
public:
  MoveBackLeftState(Program *);
  MoveBackLeftState(Program *, int);
  MoveBackLeftState(const MoveBackLeftState &) = default;
  MoveBackLeftState(MoveBackLeftState &&) = default;

  virtual ~MoveBackLeftState() = 0;

  virtual MoveBackLeftState &operator=(const MoveBackLeftState &) = default;
  virtual MoveBackLeftState &operator=(MoveBackLeftState &&) = default;

  virtual bool operator==(const MoveBackLeftState &b) const;

  virtual void run() override;
  virtual void stateInit() override;
};
#endif /*MOVE_MOVE_BACK_LEFT_STATE_H*/