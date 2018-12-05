#include "../include/managers/program_manager.h"

#include <signal.h>
#include "../include/programs/direct_search_puck_program.h"

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

    int ir_freq = 600;
    if (argc > 1 )
	ir_freq = std::stoi(argv[1]);
    ROS_INFO("Looking for frequnce %d", ir_freq);

    ProgramManager * programManager = ProgramManager::getInstance();
    Program * program = new DirectSearchPuckProgram(ir_freq);
    programManager->setProgram(program);
    programManager->start();
    delete programManager;  //deletes also program
    
    return 0;
}
