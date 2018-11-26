#ifndef PROGRAM_MANAGER_H
#define PROGRAM_MANAGER_H

#include "ros/ros.h"

#include "../../include/managers/callback_time_manager.h"
#include "../../include/managers/motor_manager.h"
#include "../../include/managers/sensor_manager.h"

#include "../programs/program.h"

struct SubscribedCallBack;

class ProgramManager
{
  public:
    ~ProgramManager();
    static ProgramManager *getInstance();
    void start();
    void setProgram(Program *program);

  private:
    ProgramManager();

    static ProgramManager *instance;

    Program *runningProgram;
    CallBackTimeManager *callback_manager = nullptr;
    MotorManager *motor_manager = nullptr;
    SensorManager *sensor_manager = nullptr;
};
#endif /*PROGRAM_MANAGER_H*/