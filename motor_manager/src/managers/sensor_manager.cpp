#include "../../include/managers/sensor_manager.h"

SensorManager *SensorManager::instance = nullptr;

SensorManager *SensorManager::getInstance()
{
    if (!instance)
        instance = new SensorManager();
    return instance;
}

SensorManager::SensorManager() : thread(nullptr), shouldEnd(false)
{
    start();
    ROS_INFO("SensorManager initialized");
}
SensorManager::~SensorManager()
{
    ROS_INFO("Joining SensorManager thread");
    shouldEnd = true;
    thread->join();
    delete thread;
    ROS_INFO("Thread SensorManager Joined");
}

void SensorManager::subscribeToAll(SensorObserver *observer)
{
    subscribePuckAquiredEvent(observer);
    subscribePuckLostEvent(observer);
    subscribeLightDetectedEvent(observer);
    subscribeLightLostEvent(observer);
    subscribeLeftTouchTriggeredEvent(observer);
    subscribeLeftTouchFreedEvent(observer);
    subscribeRightTouchTriggeredEvent(observer);
    subscribeRightTouchFreedEvent(observer);
    subscribeBothTouchTriggeredEvent(observer);
    subscribeBothTouchFreedEvent(observer);
    subscribeIR600FoundEvent(observer);
    subscribeIR600LostEvent(observer);
    subscribeIR1500FoundEvent(observer);
    subscribeIR1500LostEvent(observer);
}

void SensorManager::unsubscribeFromAll(SensorObserver *observer)
{
    puckAquiredEventHandlers.remove(observer);
    puckLostEventHandlers.remove(observer);
    leftTouchTriggeredEventHandlers.remove(observer);
    leftTouchFreedEventHandlers.remove(observer);
    rightTouchTriggeredEventHandlers.remove(observer);
    rightTouchFreedEventHandlers.remove(observer);
    bothTouchTriggeredEventHandlers.remove(observer);
    bothTouchFreedEventHandlers.remove(observer);
    lightDetectedEventHandlers.remove(observer);
    lightLostEventHandlers.remove(observer);
    ir600FoundEventHandlers.remove(observer);
    ir600LostEventHandlers.remove(observer);
    ir1500FoundEventHandlers.remove(observer);
    ir1500LostEventHandlers.remove(observer);
    //ROS_INFO("SensorManager unsubsribed %p", observer);
}

void SensorManager::subscribePuckAquiredEvent(SensorObserver *observer)
{
    puckAquiredEventHandlers.push_back(observer);
}

void SensorManager::subscribePuckLostEvent(SensorObserver *observer)
{
    puckLostEventHandlers.push_back(observer);
}

void SensorManager::subscribeLightDetectedEvent(SensorObserver *observer)
{
    lightDetectedEventHandlers.push_back(observer);
}

void SensorManager::subscribeLightLostEvent(SensorObserver *observer)
{
    lightLostEventHandlers.push_back(observer);
}

void SensorManager::subscribeLeftTouchTriggeredEvent(SensorObserver *observer)
{
    leftTouchTriggeredEventHandlers.push_back(observer);
}

void SensorManager::subscribeLeftTouchFreedEvent(SensorObserver *observer)
{
    leftTouchFreedEventHandlers.push_back(observer);
}

void SensorManager::subscribeRightTouchTriggeredEvent(SensorObserver *observer)
{
    rightTouchTriggeredEventHandlers.push_back(observer);
}

void SensorManager::subscribeRightTouchFreedEvent(SensorObserver *observer)
{
    rightTouchFreedEventHandlers.push_back(observer);
}

void SensorManager::subscribeBothTouchTriggeredEvent(SensorObserver *observer)
{
    bothTouchTriggeredEventHandlers.push_back(observer);
}

void SensorManager::subscribeBothTouchFreedEvent(SensorObserver *observer)
{
    bothTouchFreedEventHandlers.push_back(observer);
}

void SensorManager::subscribeIR600FoundEvent(SensorObserver *observer)
{
    ir600FoundEventHandlers.push_back(observer);
}
void SensorManager::subscribeIR600LostEvent(SensorObserver *observer)
{
    ir600LostEventHandlers.push_back(observer);
}

void SensorManager::subscribeIR1500FoundEvent(SensorObserver *observer)
{
    ir1500FoundEventHandlers.push_back(observer);
}
void SensorManager::subscribeIR1500LostEvent(SensorObserver *observer)
{
    ir1500LostEventHandlers.push_back(observer);
}

void SensorManager::start()
{
    ROS_INFO("Starting SensorManager");
    if (thread)
    {
        ROS_INFO("Joining previous thread for SensorManager");
        shouldEnd = true;
        thread->join();
        delete thread;
    }
    thread = new std::thread(SensorManager::run, this);
}

void SensorManager::run(SensorManager *manager)
{
    ROS_INFO("SensorManager started");
    LightSensor lightSensor(LIGHT_SENSOR_PIN);
    TouchSensor puckSensor(PUCK_SENSOR_PIN);
    TouchSensor leftSensor(LEFT_SENSOR_PIN);
    TouchSensor rightSensor(RIGHT_SENSOR_PIN);
    InfraRedSensor infraRedSensor(INFRA_RED_SENSOR_PIN);
    ros::Rate loop_rate(FREQUENCE);
    while (ros::ok() && !manager->shouldEnd)
    {
        resolveLightSensor(lightSensor, manager);
        resolveFrontSensors(leftSensor, rightSensor, manager);
        resolvePuckSensor(puckSensor, manager);
        resolveIRSensor(infraRedSensor, manager);
        loop_rate.sleep();
    }
    manager->shouldEnd = false;
}

void SensorManager::resolveLightSensor(LightSensor &sensor, SensorManager *manager)
{
    unsigned short prevState = sensor.getPreviousSignal();
    unsigned short state = sensor.checkSignal();
    if (prevState != state)
    {
        ROS_INFO("\033[1;33mLight recieved: %d\033[0m ", !state);
        if (state == 1)
            callEventHandlers(manager->lightLostEventHandlers, &SensorObserver::lightLostEventHandler);
        else
            callEventHandlers(manager->lightDetectedEventHandlers, &SensorObserver::lightDetectedEventHandler);
    }
}

void SensorManager::resolveFrontSensors(TouchSensor &left, TouchSensor &right, SensorManager *manager)
{
    bool prevLeftState = left.getPrevious();
    bool prevRightState = right.getPrevious();
    bool leftState = left.isPushed();
    bool rightState = right.isPushed();
    if (prevLeftState != leftState && prevRightState != rightState && rightState == leftState) //both changed state
    {
        ROS_INFO("Both Touch Sensors: %d, %d ", leftState, rightState);
        if (rightState)
            callEventHandlers(manager->bothTouchTriggeredEventHandlers, &SensorObserver::bothTouchTriggeredEventHandler);
        else
            callEventHandlers(manager->bothTouchFreedEventHandlers, &SensorObserver::bothTouchFreedEventHandler);
    }
    else
    {
        if (prevLeftState != leftState)
        {
            ROS_INFO("Touch sensor (left): %d ", leftState);
            if (leftState)
                callEventHandlers(manager->leftTouchTriggeredEventHandlers, &SensorObserver::leftTouchTriggeredEventHandler);
            else
                callEventHandlers(manager->leftTouchFreedEventHandlers, &SensorObserver::leftTouchFreedEventHandler);
        }
        if (prevRightState != rightState)
        {
            ROS_INFO("Touch sensor (right): %d ", rightState);
            if (rightState)
                callEventHandlers(manager->rightTouchTriggeredEventHandlers, &SensorObserver::rightTouchTriggeredEventHandler);
            else
                callEventHandlers(manager->rightTouchFreedEventHandlers, &SensorObserver::rightTouchFreedEventHandler);
        }
    }
}

void SensorManager::resolvePuckSensor(TouchSensor &sensor, SensorManager *manager)
{
    bool prevState = sensor.getPrevious();
    bool state = sensor.isPushed();
    if (prevState != state)
    {
        ROS_INFO("Touch sensor (puck): %d ", state);
        if (state)
            callEventHandlers(manager->puckAquiredEventHandlers, &SensorObserver::puckAquiredEventHandler);
        else
            callEventHandlers(manager->puckLostEventHandlers, &SensorObserver::puckLostEventHandler);
    }
}

void SensorManager::resolveIRSensor(InfraRedSensor &sensor, SensorManager *manager)
{
    auto prevState = sensor.getPreviousSignal();
    auto state = sensor.checkSignal();
    if (prevState != state)
    {
        ROS_INFO("\033[1;31mInfrared sensor: %d\033[0m", state);
        if (prevState == InfraRedSensor::SIGNAL_600)
            callEventHandlers(manager->ir600LostEventHandlers, &SensorObserver::ir600LostEventHandler);
        else if (prevState == InfraRedSensor::SIGNAL_1500)
            callEventHandlers(manager->ir1500LostEventHandlers, &SensorObserver::ir1500LostEventHandler);
        if (state == InfraRedSensor::SIGNAL_600)
            callEventHandlers(manager->ir600FoundEventHandlers, &SensorObserver::ir600FoundEventHandler);
        else if (state == InfraRedSensor::SIGNAL_1500)
            callEventHandlers(manager->ir1500FoundEventHandlers, &SensorObserver::ir1500FoundEventHandler);
    }
}

void SensorManager::callEventHandlers(const std::list<SensorObserver *> &handlers, void (SensorObserver::*ptr)())
{
    for (auto it = handlers.begin(); it != handlers.end(); it++)
    {
        ((*it)->*ptr)();
    }
}
