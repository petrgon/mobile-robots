enum CollisionSensor
{
    LEFT,
    RIGHT,
    BOTH,
    NONE
};

struct CollisionEvent
{
    CollisionEvent() : sensor(CollisionSensor::NONE) {}
    CollisionSensor sensor;
};

struct LightEvent
{
    int value;
};