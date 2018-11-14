#include "../../include/managers/callback_time_manager.h"

CallBackTimeManager *CallBackTimeManager::instance = nullptr;

CallBackTimeManager::~CallBackTimeManager()
{
    ROS_INFO("Joining CallBackTimeManager thread");
    shouldEnd = true;
    condVar.notify_all();
    thread->join();
    delete thread;
    ROS_INFO("Thread CallBackTimeManager Joined");
}

CallBackTimeManager *CallBackTimeManager::getInstance()
{
    if (!instance)
        instance = new CallBackTimeManager();
    return instance;
}

void CallBackTimeManager::subscribe(State *state, int64_t time)
{
    SubscribedCallBack callback(state, time);
    std::unique_lock<std::mutex> lck(m);
    auto it = callbackHandlers.begin();
    auto firstBigger = callbackHandlers.end();
    for (; it != callbackHandlers.end(); ++it)
    {
        if (*it >= callback)
            firstBigger = it;
        if (*it == callback)
        {
            *it = callback;
            lck.unlock();
            condVar.notify_all();
            return;
        }
    }
    callbackHandlers.insert(firstBigger, callback);
    lck.unlock();
    condVar.notify_all();
}

CallBackTimeManager::CallBackTimeManager() : thread(nullptr), shouldEnd(false)
{
    start();
    ROS_INFO("CallBackTimeManager initialized");
}

void CallBackTimeManager::start()
{
    ROS_INFO("Starting CallBackTimeManager");
    if (thread)
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
        std::unique_lock<std::mutex> lck(manager->m);
        manager->condVar.wait(lck, [manager] { return !manager->callbackHandlers.empty(); });
        auto top = manager->callbackHandlers.front();
        auto now = std::chrono::system_clock::now();
        if (top.subscribed + top.time <= now)
        {
            ROS_INFO("Calling %p after %d milisec", top.state, top.time.count());
            top.state->timeElapsedEventHandler();
            manager->callbackHandlers.pop_front();
        }
        else
        {
            auto until = top.subscribed + top.time;
            manager->condVar.wait_until(lck, until);
        }
        lck.unlock();
    }
    manager->shouldEnd = false;
}

SubscribedCallBack::SubscribedCallBack(State *state, int64_t milis)
    : state(state), time(std::chrono::milliseconds(milis)), subscribed(std::chrono::system_clock::now()) {}

SubscribedCallBack::~SubscribedCallBack() {}

SubscribedCallBack::SubscribedCallBack(const SubscribedCallBack &b)
    : state(b.state), subscribed(b.subscribed), time(b.time) {}

SubscribedCallBack::SubscribedCallBack(SubscribedCallBack &&b)
    : state(std::move(b.state)), subscribed(std::move(b.subscribed)), time(std::move(b.time)) {}

bool SubscribedCallBack::operator>(const SubscribedCallBack &b) const
{
    return subscribed + time > b.subscribed + b.time;
}
bool SubscribedCallBack::operator<(const SubscribedCallBack &b) const
{
    return b > *this;
}
bool SubscribedCallBack::operator>=(const SubscribedCallBack &b) const
{
    return !(*this < b);
}
bool SubscribedCallBack::operator<=(const SubscribedCallBack &b) const
{
    return !(*this > b);
}
bool SubscribedCallBack::operator==(const SubscribedCallBack &b) const
{
    return state == b.state;
}
bool SubscribedCallBack::operator!=(const SubscribedCallBack &b) const
{
    return !(*this == b);
}
