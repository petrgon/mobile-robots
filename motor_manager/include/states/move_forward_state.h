#ifndef MOVE_FORWARD_STATE_H
#define MOVE_FORWARD_STATE_H

#include "state.h"
#include "../managers/motor_manager.h"
#include "../managers/sensor_manager.h"
#include "../managers/callback_time_manager.h"

#define SPEED 100
#define TIME_OUT 2000

class MoveForwardState : public State
{
public:
  MoveForwardState(Program *);
  MoveForwardState(const MoveForwardState &) = default;
  MoveForwardState(MoveForwardState &&) = default;

  virtual ~MoveForwardState() = 0;

  virtual MoveForwardState &operator=(const MoveForwardState &) = default;
  virtual MoveForwardState &operator=(MoveForwardState &&) = default;

  virtual bool operator==(const MoveForwardState &b) const;

  virtual void run() override;
  virtual void stateInit() override;
  virtual void subscribe() override;
  virtual void unsubscribe() override;

};
#endif /*MOVE_FORWARD_STATE_H*/