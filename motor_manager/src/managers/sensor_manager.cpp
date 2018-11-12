#include "../../include/sensor_manager.h"

SensorManager::SensorManager() {}
SensorManager::~SensorManager()
{
    thread->join();
    delete thread;
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
    ROS_INFO("Starting SensorManager");
    thread = new std::thread(SensorManager::run, this);
}

void SensorManager::run(SensorManager *manager)
{
    ROS_INFO("SensorManager started");
    LightSensor lightSensor(LIGHT_SENSOR_PIN);
    TouchSensor puckSensor(PUCK_SENSOR_PIN);
    TouchSensor leftSensor(LEFT_SENSOR_PIN);
    TouchSensor rightSensor(RIGHT_SENSOR_PIN);
    ros::Rate loop_rate(FREQUENCE);
    while (ros::ok())
    {
        ROS_INFO("Checking sensors");
        if (puckSensor.isPushed())
            manager->callPuckAquiredHandlers();
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
            manager->callCollisionHandlers(e);
        unsigned short signal = lightSensor.checkSignal();
        if (signal > 0)
        {
            LightEvent le = {signal};
            manager->callLightHandlers(le);
        }
        loop_rate.sleep();
    }
}

void SensorManager::callLightHandlers(LightEvent e) const
{
    for (auto it = lightEventHandler.begin(); it != lightEventHandler.end(); it++)
    {
        (*it)(e);
    }
}
void SensorManager::callCollisionHandlers(CollisionEvent e) const
{
    for (auto it = collisionEventHandler.begin(); it != collisionEventHandler.end(); it++)
    {
        (*it)(e);
    }
}
void SensorManager::callPuckAquiredHandlers() const
{
    for (auto it = puckAquiredEventHandler.begin(); it != puckAquiredEventHandler.end(); it++)
    {
        (*it)();
    }
}
