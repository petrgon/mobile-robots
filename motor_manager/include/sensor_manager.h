#ifndef SENSOR_MANAGER_H
#define SENSOR_MANAGER_H

#include "ros/ros.h"
#include "std_msgs/Int32MultiArray.h"

#include "events.h"
#include "light_sensor.h"
#include "touch_sensor.h"

#include <vector>
#include <thread>

#define FREQUENCE 10 //10Hz

#define LIGHT_SENSOR_PIN 7
#define LEFT_SENSOR_PIN 5
#define RIGHT_SENSOR_PIN 1
#define PUCK_SENSOR_PIN 4

class SensorManager
{
  public:

    SensorManager();
    ~SensorManager();

    void subscribeLightEvent(void(*fnc)(LightEvent));

    void subscribeCollisionEvent(void (*fnc)(CollisionEvent));

    void subscribePuckAquiredEvent(void (*fnc)());

    void start();

  private:
    void callLightHandlers(LightEvent e) const;
    void callCollisionHandlers(CollisionEvent e) const;
    void callPuckAquiredHandlers() const;

    static void run(SensorManager  *manager);

    std::vector<void (*)(LightEvent)> lightEventHandler;
    std::vector<void (*)(CollisionEvent)> collisionEventHandler;
    std::vector<void (*)()> puckAquiredEventHandler;

    std::thread thread;
};
#endif /*SENSOR_MANAGER_H*/
