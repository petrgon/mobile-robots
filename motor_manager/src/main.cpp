#include "../include/managers/program_manager.h"

#include <signal.h>
#include "../include/programs/direct_search_puck_program.h"

ProgramManager *programManager = nullptr;

void SIGINT_handler(int sig)
{
    programManager->end();
}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "robot_core", ros::init_options::NoSigintHandler);
    signal(SIGINT, SIGINT_handler);
    ROS_INFO("ROS initialized");
    setenv("WIRINGPI_GPIOMEM", "1", 1);
    wiringPiSetup();
    ROS_INFO("WiringPI initialized");
    programManager = ProgramManager::getInstance();
    
    int params[4];
    if (argc <= 1){
        ROS_INFO("Invalid number of params. Program needs 1 or 4 params.\n  INFRA_RED_FREQ, LEFT_SPEED, RIGHT_SPEED, FORWARD_TIME\nor\n  IFRA_RED_FREQ");
        ros::shutdown();
        return 1;
    }
    for (int i = 1; i < argc; i++)
        params[i - 1] = std::stoi(argv[i]);
    ROS_INFO("Looking for frequnce %d", params[0]);
    Program *program;
    if(argc == 5){
        program = new DirectSearchPuckProgram(params[0], params[1], params[2], params[3]);
        ROS_INFO("Program params (%d, %d, %d, %d)", params[0], params[1], params[2], params[3]);
    }
    else{
        program = new DirectSearchPuckProgram(params[0]);
        ROS_INFO("Program params (%d)", params[0]);
    }
    programManager->setProgram(program);

    char starter;
    std::cin >> starter;

    programManager->start();

    delete (programManager);
    programManager = nullptr;
    ros::shutdown();
    return 0;
}
