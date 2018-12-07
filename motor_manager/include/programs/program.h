#ifndef PROGRAM_H
#define PROGRAM_H

#include "../sensor_observer.h"
#include <atomic>
#include <string>

class State;

class Program : public SensorObserver
{
public:
  Program();
  Program(const Program &) = default;
  Program(Program &&) = default;

  virtual ~Program() = 0;

  virtual Program &operator=(const Program &) = default;
  virtual Program &operator=(Program &&) = default;

  virtual void run();
  virtual void changeState(State *nextState);
  virtual std::string getName();

protected:
  State *actualState;
  State *nextState;

  State **allStates;
  int stateConut;
};

#endif /*PROGRAM_H*/