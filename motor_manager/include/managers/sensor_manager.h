#ifndef SENSOR_MANAGER_H
#define SENSOR_MANAGER_H

#include "ros/ros.h"

#include "../sensors/light_sensor.h"
#include "../sensors/touch_sensor.h"
#include "../sensors/infra_red_sensor.h"
#include "../sensor_observer.h"

#include <list>
#include <thread>

#define FREQUENCE 10 //10Hz

#define LIGHT_SENSOR_PIN 7
#define LEFT_SENSOR_PIN 5
#define RIGHT_SENSOR_PIN 1
#define PUCK_SENSOR_PIN 4
#define INFRA_RED_SENSOR_PIN 0

class SensorManager
{
public:
  static SensorManager *getInstance();

  ~SensorManager();

  void subscribeToAll(SensorObserver *);
  void unsubscribeFromAll(SensorObserver *);

  void subscribeLightDetectedEvent(SensorObserver *);
  void subscribeLightLostEvent(SensorObserver *);

  void subscribeLeftTouchTriggeredEvent(SensorObserver *);
  void subscribeLeftTouchFreedEvent(SensorObserver *);

  void subscribeRightTouchTriggeredEvent(SensorObserver *);
  void subscribeRightTouchFreedEvent(SensorObserver *);

  void subscribeBothTouchTriggeredEvent(SensorObserver *);
  void subscribeBothTouchFreedEvent(SensorObserver *);

  void subscribePuckAquiredEvent(SensorObserver *);
  void subscribePuckLostEvent(SensorObserver *);
  
  void subscribeIR600FoundEvent(SensorObserver *);
  void subscribeIR600LostEvent(SensorObserver *);

  void subscribeIR1500FoundEvent(SensorObserver *);
  void subscribeIR1500LostEvent(SensorObserver *);

private:
  SensorManager();
  
  void start();

  static void resolveLightSensor(LightSensor &sensor, SensorManager *manager);

  static void resolveFrontSensors(TouchSensor &left, TouchSensor &right, SensorManager *manager);

  static void resolvePuckSensor(TouchSensor &sensor, SensorManager *manager);

  static void resolveIRSensor(InfraRedSensor &sensor, SensorManager *manager);

  static void callEventHandlers(const std::list<SensorObserver *> &handlers, void (SensorObserver::*ptr)());

  static void run(SensorManager *manager);

  std::list<SensorObserver *> lightDetectedEventHandlers;
  std::list<SensorObserver *> lightLostEventHandlers;
  std::list<SensorObserver *> puckAquiredEventHandlers;
  std::list<SensorObserver *> puckLostEventHandlers;
  std::list<SensorObserver *> leftTouchTriggeredEventHandlers;
  std::list<SensorObserver *> leftTouchFreedEventHandlers;
  std::list<SensorObserver *> rightTouchTriggeredEventHandlers;
  std::list<SensorObserver *> rightTouchFreedEventHandlers;
  std::list<SensorObserver *> bothTouchTriggeredEventHandlers;
  std::list<SensorObserver *> bothTouchFreedEventHandlers;
  std::list<SensorObserver *> ir600FoundEventHandlers;
  std::list<SensorObserver *> ir600LostEventHandlers;
  std::list<SensorObserver *> ir1500FoundEventHandlers;
  std::list<SensorObserver *> ir1500LostEventHandlers;

  std::thread *thread;
  bool shouldEnd;

  static SensorManager *instance;
};
#endif /*SENSOR_MANAGER_H*/
