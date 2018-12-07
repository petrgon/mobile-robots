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

void CallBackTimeManager::subscribe(SensorObserver *observer, int64_t time)
{
    SubscribedCallBack callback(observer, time);
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

void CallBackTimeManager::unsubscribe(SensorObserver *observer)
{
    std::unique_lock<std::mutex> lck(m);
    callbackHandlers.remove_if([observer](const SubscribedCallBack & a) { return a.observer == observer; });
    //ROS_INFO("CallbackTime unsubscribed %p", observer);
    lck.unlock();
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
        if(manager->callbackHandlers.empty())
            continue;
        auto top = manager->callbackHandlers.front();
        auto now = std::chrono::system_clock::now();
        if (top.subscribed + top.time <= now)
        {
            ROS_INFO("Calling %p after %d milisec", top.observer, top.time.count());
            top.observer->timeElapsedEventHandler();
            manager->callbackHandlers.pop_front();
        }
        else
        {
            //auto until = top.subscribed + top.time;
            //manager->condVar.wait_until(lck, 50, [manager] { return manager->shouldEnd; });
        }
        lck.unlock();
    }
    manager->shouldEnd = false;
}

SubscribedCallBack::SubscribedCallBack(SensorObserver *observer, int64_t milis)
    : observer(observer), time(std::chrono::milliseconds(milis)), subscribed(std::chrono::system_clock::now()) {}

SubscribedCallBack::~SubscribedCallBack() {}

SubscribedCallBack::SubscribedCallBack(const SubscribedCallBack &b)
    : observer(b.observer), time(b.time) , subscribed(b.subscribed){}

SubscribedCallBack::SubscribedCallBack(SubscribedCallBack &&b)
    : observer(std::move(b.observer)), time(std::move(b.time)), subscribed(std::move(b.subscribed)) {}

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
    return observer == b.observer;
}
bool SubscribedCallBack::operator!=(const SubscribedCallBack &b) const
{
    return !(*this == b);
}
