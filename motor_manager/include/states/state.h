#ifndef STATE_H
#define STATE_H

#include "../sensor_observer.h"
#include "../programs/program.h"

class State : public SensorObserver
{
public:
  State(Program *);
  State(const State &) = default;
  State(State &&) = default;

  virtual ~State() = 0;

  virtual State &operator=(const State &) = default;
  virtual State &operator=(State &&) = default;

  virtual bool operator==(const State &b) const;

  virtual void run() = 0;
  virtual void stateInit();
  virtual void subscribe();
  virtual void unsubscribe();

protected:
  Program *program;
};
#endif /*STATE_H*/