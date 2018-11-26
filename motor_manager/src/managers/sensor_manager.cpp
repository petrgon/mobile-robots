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

void SensorManager::subscribeToAll(Program *program)
{
    subscribePuckAquiredEvent(program);
    subscribePuckLostEvent(program);
    subscribeLightDetectedEvent(program);
    subscribeLightLostEvent(program);
    subscribeLeftTouchTriggeredEvent(program);
    subscribeLeftTouchFreedEvent(program);
    subscribeRightTouchTriggeredEvent(program);
    subscribeRightTouchFreedEvent(program);
    subscribeBothTouchTriggeredEvent(program);
    subscribeBothTouchFreedEvent(program);
}

void SensorManager::unsubscribeFromAll(Program *program)
{
    puckAquiredEventHandlers.remove(program);
    puckLostEventHandlers.remove(program);
    leftTouchTriggeredEventHandlers.remove(program);
    leftTouchFreedEventHandlers.remove(program);
    rightTouchTriggeredEventHandlers.remove(program);
    rightTouchFreedEventHandlers.remove(program);
    bothTouchTriggeredEventHandlers.remove(program);
    bothTouchFreedEventHandlers.remove(program);
    lightDetectedEventHandlers.remove(program);
    lightLostEventHandlers.remove(program);
}

void SensorManager::subscribePuckAquiredEvent(Program *program)
{
    puckAquiredEventHandlers.push_back(program);
}

void SensorManager::subscribePuckLostEvent(Program *program)
{
    puckLostEventHandlers.push_back(program);
}

void SensorManager::subscribeLightDetectedEvent(Program *program)
{
    lightDetectedEventHandlers.push_back(program);
}

void SensorManager::subscribeLightLostEvent(Program *program)
{
    lightLostEventHandlers.push_back(program);
}

void SensorManager::subscribeLeftTouchTriggeredEvent(Program *program)
{
    leftTouchTriggeredEventHandlers.push_back(program);
}

void SensorManager::subscribeLeftTouchFreedEvent(Program *program)
{
    leftTouchFreedEventHandlers.push_back(program);
}

void SensorManager::subscribeRightTouchTriggeredEvent(Program *program)
{
    rightTouchTriggeredEventHandlers.push_back(program);
}

void SensorManager::subscribeRightTouchFreedEvent(Program *program)
{
    rightTouchFreedEventHandlers.push_back(program);
}

void SensorManager::subscribeBothTouchTriggeredEvent(Program *program)
{
    bothTouchTriggeredEventHandlers.push_back(program);
}

void SensorManager::subscribeBothTouchFreedEvent(Program *program)
{
    bothTouchFreedEventHandlers.push_back(program);
}

void SensorManager::subscribeIR600FoundEvent(Program *program)
{
    ir600FoundEventHandlers.push_back(program);
}
void SensorManager::subscribeIR600LostEvent(Program *program)
{
    ir600LostEventHandlers.push_back(program);
}

void SensorManager::subscribeIR1500FoundEvent(Program *program)
{
    ir1500FoundEventHandlers.push_back(program);
}
void SensorManager::subscribeIR1500LostEvent(Program *program)
{
    ir1500LostEventHandlers.push_back(program);
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
        ROS_INFO("Light recieved: %d ", state);
        if (state == 1)
            callEventHandlers(manager->lightLostEventHandlers, &Program::lightLostEventHandler);
        else
            callEventHandlers(manager->lightDetectedEventHandlers, &Program::lightDetectedEventHandler);
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
        ROS_INFO("Touch sensor (left): %d ", leftState);
        ROS_INFO("Touch sensor (right): %d ", rightState);
        if (rightState)
            callEventHandlers(manager->bothTouchTriggeredEventHandlers, &Program::bothTouchTriggeredEventHandler);
        else
            callEventHandlers(manager->bothTouchFreedEventHandlers, &Program::bothTouchFreedEventHandler);
    }
    else
    {
        if (prevLeftState != leftState)
        {
            ROS_INFO("Touch sensor (left): %d ", leftState);
            if (leftState)
                callEventHandlers(manager->leftTouchTriggeredEventHandlers, &Program::leftTouchTriggeredEventHandler);
            else
                callEventHandlers(manager->leftTouchFreedEventHandlers, &Program::leftTouchFreedEventHandler);
        }
        if (prevRightState != rightState)
        {
            ROS_INFO("Touch sensor (right): %d ", rightState);
            if (rightState)
                callEventHandlers(manager->rightTouchTriggeredEventHandlers, &Program::rightTouchTriggeredEventHandler);
            else
                callEventHandlers(manager->rightTouchFreedEventHandlers, &Program::rightTouchFreedEventHandler);
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
            callEventHandlers(manager->puckAquiredEventHandlers, &Program::puckAquiredEventHandler);
        else
            callEventHandlers(manager->puckLostEventHandlers, &Program::puckLostEventHandler);
    }
}

void SensorManager::resolveIRSensor(InfraRedSensor &sensor, SensorManager *manager)
{
    unsigned short int prevState = sensor.getPreviousSignal();
    unsigned short int state = sensor.checkSignal();
    if (prevState != state)
    {
        ROS_INFO("IR sensor: %d ", state);
        if (state == 0)
        {
            if (prevState == InfraRedSensor::SIGNAL_600)
                callEventHandlers(manager->ir600LostEventHandlers, &Program::ir600LostEventHandler);
            else if (prevState == InfraRedSensor::SIGNAL_1500)
                callEventHandlers(manager->ir1500LostEventHandlers, &Program::ir1500LostEventHandler);
            else
                ROS_ERROR("IR Sensor invalid previous value: %d ", prevState);
        }
        else
        {
            if (state == InfraRedSensor::SIGNAL_600)
                callEventHandlers(manager->ir600FoundEventHandlers, &Program::ir600FoundEventHandler);
            else if (state == InfraRedSensor::SIGNAL_1500)
                callEventHandlers(manager->ir1500FoundEventHandlers, &Program::ir1500FoundEventHandler);
            else
                ROS_ERROR("IR Sensor invalid value: %d ", state);
        }
    }
}

void SensorManager::callEventHandlers(const std::list<Program *> &handlers, void (Program::*ptr)())
{
    for (auto it = handlers.begin(); it != handlers.end(); it++)
    {
        ((*it)->*ptr)();
    }
}
