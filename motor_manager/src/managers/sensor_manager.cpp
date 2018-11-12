#include "../../include/sensor_manager.h"

SensorManager::SensorManager() {}
SensorManager::~SensorManager()
{
    thread.join();
}

void SensorManager::subscribeLightEvent(void (*fnc)(LightEvent))
{
    lightEventHandler.push_back(fnc);
}

void SensorManager::subscribeCollisionEvent(void (*fnc)(CollisionEvent))
{
    collisionEventHandler.push_back(fnc);
}

void SensorManager::subscribePuckAquiredEvent(void (*fnc)())
{
    puckAquiredEventHandler.push_back(fnc);
}

void SensorManager::start()
{
    thread = std::thread(run);
}

void SensorManager::run()
{
    LightSensor lightSensor(LIGHT_SENSOR_PIN);
    TouchSensor puckSensor(PUCK_SENSOR_PIN);
    TouchSensor leftSensor(LEFT_SENSOR_PIN);
    TouchSensor rightSensor(RIGHT_SENSOR_PIN);
    ros::Rate loop_rate(FREQUENCE);
    while (ros::ok())
    {
        if (puckSensor.isPushed())
            callPuckAquiredHandlers();
        CollisionEvent e;
        if (leftSensor.isPushed())
            e.sensor = CollisionSensor::LEFT;
        if (rightSensor.isPushed())
        {
            if (e.sensor == CollisionSensor::LEFT)
                e.sensor = CollisionSensor::BOTH;
            else
                e.sensor = CollisionSensor::RIGHT;
        }
        if (e.sensor != CollisionSensor::NONE)
            callCollisionHandlers(e);
        unsigned short signal = lightSensor.checkSignal();
        if (signal > 0)
        {
            LightEvent le = {signal};
            callLightHandlers(le);
        }
        loop_rate.sleep();
    }
}

void SensorManager::callLightHandlers(LightEvent e)
{
    for (auto it = lightEventHandler.begin(); it != lightEventHandler.end(); it++)
    {
        (*it)(e);
    }
}
void SensorManager::callCollisionHandlers(CollisionEvent e)
{
    for (auto it = collisionEventHandler.begin(); it != collisionEventHandler.end(); it++)
    {
        (*it)(e);
    }
}
void SensorManager::callPuckAquiredHandlers()
{
    for (auto it = puckAquiredEventHandler.begin(); it != puckAquiredEventHandler.end(); it++)
    {
        (*it)();
    }
}