#include "../include/sensor_observer.h"

SensorObserver::SensorObserver() {}

SensorObserver::~SensorObserver() {}

bool SensorObserver::operator==(const SensorObserver &b) const
{
    return this == &b;
}

void SensorObserver::timeElapsedEventHandler() {}

void SensorObserver::puckAquiredEventHandler() {}
void SensorObserver::puckLostEventHandler() {}

void SensorObserver::lightDetectedEventHandler() {}
void SensorObserver::lightLostEventHandler() {}

void SensorObserver::leftTouchTriggeredEventHandler() {}
void SensorObserver::leftTouchFreedEventHandler() {}

void SensorObserver::rightTouchTriggeredEventHandler() {}
void SensorObserver::rightTouchFreedEventHandler() {}

void SensorObserver::bothTouchTriggeredEventHandler() {}
void SensorObserver::bothTouchFreedEventHandler() {}

void SensorObserver::ir600FoundEventHandler() {}
void SensorObserver::ir600LostEventHandler() {}

void SensorObserver::ir1500FoundEventHandler() {}
void SensorObserver::ir1500LostEventHandler() {}