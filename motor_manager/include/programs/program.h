#ifndef STATE_MANAGER_H
#define STATE_MANAGER_H

#include "../sensor_observer.h"
#include "../states/state.h"
#include <atomic>

class Program : public SensorObserver
{
public:
  Program();
  Program(const Program &) = default;
  Program(Program &&) = default;

  virtual ~Program() = 0;

  virtual Program &operator=(const Program &) = default;
  virtual Program &operator=(Program &&) = default;

  virtual bool operator==(const Program &b) const;

  virtual void run();
  virtual void changeState(unsigned int nextState);

protected:
  State *actualState;
  unsigned int nextState;

  State *allStates;
  int stateConut;
};

#endif /*STATE_MANAGER_H*/