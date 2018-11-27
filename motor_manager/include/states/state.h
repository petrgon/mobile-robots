#ifndef STATE_H
#define STATE_H

#include "../sensor_observer.h"
#include "../programs/program.h"
#include "../managers/callback_time_manager.h"
#include "../managers/sensor_manager.h"

class State : public SensorObserver
{
public:
  State(Program *);
  State(Program *, int timeOut);
  State(const State &) = default;
  State(State &&) = default;

  virtual ~State() = 0;

  virtual State &operator=(const State &) = default;
  virtual State &operator=(State &&) = default;

  virtual bool operator==(const State &b) const;
  
  virtual State * setTimeElapsedNextState(State *);

  virtual State * setPuckAquiredNextState(State *);
  virtual State * setPuckLostNextState(State *);

  virtual State * setLightDetectedNextState(State *);
  virtual State * setLightLostNextState(State *);

  virtual State * setLeftTouchTriggeredNextState(State *);
  virtual State * setLeftTouchFreedNextState(State *);

  virtual State * setRightTouchTriggeredNextState(State *);
  virtual State * setRightTouchFreedNextState(State *);

  virtual State * setBothTouchTriggeredNextState(State *);
  virtual State * setBothTouchFreedNextState(State *);

  virtual State * setIr600FoundNextState(State *);
  virtual State * setIr600LostNextState(State *);

  virtual State * setIr1500FoundNextState(State *);
  virtual State * setIr1500LostNextState(State *);
  
  virtual void timeElapsedEventHandler() override;

  virtual void puckAquiredEventHandler() override;
  virtual void puckLostEventHandler() override;

  virtual void lightDetectedEventHandler() override;
  virtual void lightLostEventHandler() override;

  virtual void leftTouchTriggeredEventHandler() override;
  virtual void leftTouchFreedEventHandler() override;

  virtual void rightTouchTriggeredEventHandler() override;
  virtual void rightTouchFreedEventHandler() override;

  virtual void bothTouchTriggeredEventHandler() override;
  virtual void bothTouchFreedEventHandler() override;

  virtual void ir600FoundEventHandler() override;
  virtual void ir600LostEventHandler() override;

  virtual void ir1500FoundEventHandler() override;
  virtual void ir1500LostEventHandler() override;

  virtual void run() = 0;
  virtual void stateInit();

protected:
  virtual void unsubscribe();

  Program *program;
  int timeOut;
  bool isActive;

  State *timeElapsedNextState;

  State *puckAquiredNextState;
  State *puckLostNextState;

  State *lightDetectedNextState;
  State *lightLostNextState;

  State *leftTouchTriggeredNextState;
  State *leftTouchFreedNextState;

  State *rightTouchTriggeredNextState;
  State *rightTouchFreedNextState;

  State *bothTouchTriggeredNextState;
  State *bothTouchFreedNextState;

  State *ir600FoundNextState;
  State *ir600LostNextState;

  State *ir1500FoundNextState;
  State *ir1500LostNextState;
};
#endif /*STATE_H*/