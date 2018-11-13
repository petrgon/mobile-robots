#ifndef MOTOR_MANAGER_H
#define MOTOR_MANAGER_H

#include "ros/ros.h"

#include <queue>
#include <thread>

#include "../states/state.h"

struct SubscribedCallBack;

class CallBackTimeManager
{
  public:
    ~CallBackTimeManager();
    static CallBackTimeManager *getInstance();

    void subscribe(State *, int64_t nanosec);

  private:
    CallBackTimeManager();

    void start();
    static void run(CallBackTimeManager *manager));

    static CallBackTimeManager *instance;

    std::thread *thread;
    bool shouldEnd;

    std::priority_queue<SubscribedCallBack> callbackHandlers;
};

struct SubscribedCallBack
{
    SubscribedCallBack(State *, int64_t);
    ~SubscribedCallBack();
    SubscribedCallBack(const SubscribedCallBack &) = default;
    SubscribedCallBack(SubscribedCallBack &&) = default;
    SubscribedCallBack & operator=(const SubscribedCallBack &) = default;
    SubscribedCallBack & operator=(SubscribedCallBack &&) = default;
    bool operator > (const SubscribedCallBack &);
    bool operator < (const SubscribedCallBack &);
    bool operator >= (const SubscribedCallBack &);
    bool operator <= (const SubscribedCallBack &);
    bool operator == (const SubscribedCallBack &);
    bool operator != (const SubscribedCallBack &);

    State *state;
    std::chrono::nanoseconds time;
    std::chrono::time_point<std::chrono::system_clock> subscribed;
};
#endif /*MOTOR_MANAGER_H*/