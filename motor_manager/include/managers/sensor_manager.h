#ifndef SENSOR_MANAGER_H
#define SENSOR_MANAGER_H

#include "ros/ros.h"

#include "../sensors/light_sensor.h"
#include "../sensors/touch_sensor.h"
#include "../programs/program.h"

#include <list>
#include <thread>

#define FREQUENCE 10 //10Hz

#define LIGHT_SENSOR_PIN 7
#define LEFT_SENSOR_PIN 5
#define RIGHT_SENSOR_PIN 1
#define PUCK_SENSOR_PIN 4

class SensorManager
{
public:
  static SensorManager *getInstance();

  ~SensorManager();

  void subscribeToAll(Program *);
  void unsubscribeFromAll(Program *);

  void subscribeLightDetectedEvent(Program *);
  void subscribeLightLostEvent(Program *);

  void subscribeLeftTouchTriggeredEvent(Program *);
  void subscribeLeftTouchFreedEvent(Program *);

  void subscribeRightTouchTriggeredEvent(Program *);
  void subscribeRightTouchFreedEvent(Program *);

  void subscribeBothTouchTriggeredEvent(Program *);
  void subscribeBothTouchFreedEvent(Program *);

  void subscribePuckAquiredEvent(Program *);
  void subscribePuckLostEvent(Program *);

private:
  SensorManager();
  
  void start();

  static void resolveLightSensor(LightSensor &sensor, SensorManager *manager);

  static void resolveFrontSensors(TouchSensor &left, TouchSensor &right, SensorManager *manager);

  static void resolvePuckSensor(TouchSensor &sensor, SensorManager *manager);

  static void callEventHandlers(const std::list<Program *> &handlers, void (Program::*ptr)());

  static void run(SensorManager *manager);

  std::list<Program *> lightDetectedEventHandlers;
  std::list<Program *> lightLostEventHandlers;
  std::list<Program *> puckAquiredEventHandlers;
  std::list<Program *> puckLostEventHandlers;
  std::list<Program *> leftTouchTriggeredEventHandlers;
  std::list<Program *> leftTouchFreedEventHandlers;
  std::list<Program *> rightTouchTriggeredEventHandlers;
  std::list<Program *> rightTouchFreedEventHandlers;
  std::list<Program *> bothTouchTriggeredEventHandlers;
  std::list<Program *> bothTouchFreedEventHandlers;

  std::thread *thread;
  bool shouldEnd;

  static SensorManager *instance;
};
#endif /*SENSOR_MANAGER_H*/
