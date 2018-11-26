#ifndef CALLBACK_TIME_MANAGER_H
#define CALLBACK_TIME_MANAGER_H

#include "ros/ros.h"

#include <list>
#include <thread>
#include <condition_variable>
#include <mutex>

#include "../programs/program.h"
#include "../sensor_observer.h"

// TODO rename Program to SensorObserver

struct SubscribedCallBack;

class CallBackTimeManager
{
  public:
    ~CallBackTimeManager();
    static CallBackTimeManager *getInstance();

    void subscribe(Program *, int64_t milis);
    void unsubscribe(SensorObserver *);

  private:
    CallBackTimeManager();

    void start();
    static void run(CallBackTimeManager *manager);

    static CallBackTimeManager *instance;

    std::thread *thread;
    std::mutex m;
    std::condition_variable condVar;
    bool shouldEnd;

    std::list<SubscribedCallBack> callbackHandlers;
};

struct SubscribedCallBack
{
    SubscribedCallBack(Program *, int64_t);
    ~SubscribedCallBack();
    SubscribedCallBack(const SubscribedCallBack &);
    SubscribedCallBack(SubscribedCallBack &&);
    SubscribedCallBack &operator=(const SubscribedCallBack &) = default;
    SubscribedCallBack &operator=(SubscribedCallBack &&) = default;
    bool operator>(const SubscribedCallBack &) const;
    bool operator<(const SubscribedCallBack &) const;
    bool operator>=(const SubscribedCallBack &) const;
    bool operator<=(const SubscribedCallBack &) const;
    bool operator==(const SubscribedCallBack &) const;
    bool operator!=(const SubscribedCallBack &) const;

    Program *program;
    std::chrono::milliseconds time;
    std::chrono::time_point<std::chrono::system_clock> subscribed;
};
#endif /*CALLBACK_TIME_MANAGER_H*/