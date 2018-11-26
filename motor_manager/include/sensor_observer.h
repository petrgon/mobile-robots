#ifndef SENSOR_OBSERVER_H
#define SENSOR_OBSERVER_H

class SensorObserver
{
public:
  SensorObserver();
  SensorObserver(const SensorObserver &) = default;
  SensorObserver(SensorObserver &&) = default;

  virtual ~SensorObserver() = 0;

  virtual SensorObserver &operator=(const SensorObserver &) = default;
  virtual SensorObserver &operator=(SensorObserver &&) = default;

  virtual bool operator==(const SensorObserver &b) const;

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
#endif /*SENSOR_OBSERVER_H*/