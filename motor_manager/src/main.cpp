#include "../include/managers/program_manager.h"

#include <signal.h>
#include "../../include/programs/get_puck_program.h"

void SIGINT_handler(int sig)
{
    delete (ProgramManager::getInstance());
    ros::shutdown();
}

int main(int argc, char **argv)
{   
    ros::init(argc, argv, "robot_core", ros::init_options::NoSigintHandler);
    signal(SIGINT, SIGINT_handler);
    ROS_INFO("ROS initialized");
    setenv("WIRINGPI_GPIOMEM", "1", 1);
    wiringPiSetup();
    ROS_INFO("WiringPI initialized");

    ProgramManager * programManager = ProgramManager::getInstance();
    Program * program = new GetPuckState();
    programManager->setProgram(program);
    programManager->start();
    delete programManager;  //deletes also program
    
    return 0;
}
