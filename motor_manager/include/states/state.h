#ifndef STATE_MANAGER_H
#define STATE_MANAGER_H

class State
{
public:
  State();
  State(const State &) = default;
  State(State &&) = default;

  virtual ~State() = 0;

  virtual State &operator=(const State &) = default;
  virtual State &operator=(State &&) = default;

  virtual bool operator==(const State &b) const;

  virtual void run() = 0;

  virtual void timeElapsedEventHandler();

  virtual void puckAquiredEventHandler();
  virtual void puckLostEventHandler();

  virtual void lightDetectedEventHandler();
  virtual void lightLostEventHandler();

  virtual void leftTouchTriggeredEventHandler();
  virtual void leftTouchFreedEventHandler();

  virtual void rightTouchTriggeredEventHandler();
  virtual void rightTouchFreedEventHandler();

  virtual void bothTouchTriggeredEventHandler();
  virtual void bothTouchFreedEventHandler();
};
#endif /*STATE_MANAGER_H*/