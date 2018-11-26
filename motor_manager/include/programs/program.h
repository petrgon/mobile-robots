#ifndef STATE_MANAGER_H
#define STATE_MANAGER_H

class Program
{
public:
  Program();
  Program(const Program &) = default;
  Program(Program &&) = default;

  virtual ~Program() = 0;

  virtual Program &operator=(const Program &) = default;
  virtual Program &operator=(Program &&) = default;

  virtual bool operator==(const Program &b) const;

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

  virtual void ir600FoundEventHandler();
  virtual void ir600LostEventHandler();

  virtual void ir1500FoundEventHandler();
  virtual void ir1500LostEventHandler();
};
#endif /*STATE_MANAGER_H*/