#include "../../include/managers/program_manager.h"

ProgramManager *ProgramManager::instance = nullptr;

ProgramManager::ProgramManager() : runningProgram(nullptr),
                                   callback_manager(CallBackTimeManager::getInstance()),
                                   motor_manager(MotorManager::getInstance()),
                                   sensor_manager(SensorManager::getInstance()),
                                   nextProgram(nullptr) {}

ProgramManager::~ProgramManager()
{
    if (callback_manager)
    {
        delete callback_manager; //keep order
        callback_manager = nullptr;
    }
    if (sensor_manager)
    {
        delete sensor_manager;
        sensor_manager = nullptr;
    }
    if (motor_manager)
    {
        delete motor_manager;
        motor_manager = nullptr;
    }
    delete runningProgram;
    instance = nullptr;
    ros::shutdown();
}

ProgramManager *ProgramManager::getInstance()
{
    if (!instance)
        instance = new ProgramManager();
    return instance;
}

void ProgramManager::start()
{
    ROS_INFO("ProgramManager start called");
    while (ros::ok())
    {
        if (nextProgram){
            changeProgram();
        }
        runningProgram->run();
        ros::spinOnce();
    }
}

void ProgramManager::setProgram(Program *program)
{
    nextProgram = program;
}

void ProgramManager::changeProgram(){
    ROS_INFO("Changing running program");
    delete runningProgram;
    runningProgram = nextProgram;
    nextProgram = nullptr;
}