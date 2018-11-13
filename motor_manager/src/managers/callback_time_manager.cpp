#include "../../include/managers/callback_time_manager.h"

CallBackTimeManager *CallBackTimeManager::instance = new CallBackTimeManager();

CallBackTimeManager::~CallBackTimeManager()
{
    ROS_INFO("Joining CallBackTimeManager thread");
    shouldEnd = true;
    thread->join();
    delete thread;
    ROS_INFO("Thread CallBackTimeManager Joined");
}

CallBackTimeManager *CallBackTimeManager::getInstance()
{
    if (!instance)
        instance = new CallBackTimeManager();
    return instance
}

void CallBackTimeManager::subscribe(State *state, int64_t time)
{
    SubscribedCallBack callback(state, time);
    callbackHandlers.push(callback)
}

CallBackTimeManager::CallBackTimeManager() : thread(nullptr), shouldEnd(false)
{
    start();
    ROS_INFO("CallBackTimeManager initialized");
}

void CallBackTimeManager::start()
{
    ROS_INFO("Starting CallBackTimeManager");
    if (!thread)
    {
        ROS_INFO("Joining previous thread for CallBackTimeManager");
        shouldEnd = true;
        thread->join();
        delete thread;
    }
    thread = new std::thread(CallBackTimeManager::run, this);
}

void CallBackTimeManager::run(CallBackTimeManager *manager)
{
    while (!manager->shouldEnd && ros::ok())
    {
        auto top = manager->callbackHandlers.top;
        auto now = std::chrono::system_clock::now()
        if (top->subscribed + top->time <= now)
        {
            top->state->timeElapsedEventHandler();
            manager->callbackHandlers.pop;
        }
        else
        {
            auto left = top->subscribed + top->time - now
            std::this_thread::sleep_for(left);
        }
    }
    manager->shouldEnd = false;
}

SubscribedCallBack::SubscribedCallBack(State *state, int64_t dur)
    : state(state), time(std::chrono::nanoseconds(dur)), subscribed(std::chrono::system_clock::now()) {}

bool SubscribedCallBack::operator>(const SubscribedCallBack &b)
{
    return subscribed + time > b.subscribed + b.time;
}
bool SubscribedCallBack::operator<(const SubscribedCallBack &b)
{
    return subscribed + time < b.subscribed + b.time;
}
bool SubscribedCallBack::operator>=(const SubscribedCallBack &b)
{
    return !operator<(b);
}
bool SubscribedCallBack::operator<=(const SubscribedCallBack &b)
{
    return !operator>(b);
}
bool SubscribedCallBack::operator==(const SubscribedCallBack &b)
{
    return !operator>(b) && !operator<(b);
}
bool SubscribedCallBack::operator!=(const SubscribedCallBack &b)
{
    return !operator==(b);
}
