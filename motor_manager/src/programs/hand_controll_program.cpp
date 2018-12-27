#include "../../include/programs/hand_controll_program.h"

HandControllProgram::HandControllProgram() : Program()
{
    srvFd = createServerFd(IP_ADDRESS, PORT);
    if (srvFd == -1)
    {
        ROS_INFO("\033[1;31mEnable to create server.\033[0m");
    }
}

HandControllProgram::~HandControllProgram()
{
    close(srvFd);
}

std::string HandControllProgram::getName()
{
    return "Hand Controll Program";
}

void HandControllProgram::run()
{
    ROS_INFO("Running hand controll program");
    while (1)
    {
        struct sockaddr sa;
        socklen_t saSize = sizeof(sa);
        int cliFd = accept(srvFd, &sa, &saSize);
        ROS_INFO("Client accepter, ID= %d ", cliFd);
        serveClient(cliFd);
    }
}

int HandControllProgram::createServerFd(const char *hostName, int port)
{
    struct addrinfo *ai;
    char portStr[20];
    int fd;

    snprintf(portStr, sizeof(portStr), "%d", port);
    if (getaddrinfo(hostName, portStr, NULL, &ai) != 0)
    {
        ROS_INFO("\033[1;31mgetaddrinfo failed\033[0m");
        return -1;
    }

    fd = socket(ai->ai_family, SOCK_STREAM, 0);
    if (fd == -1)
    {
        ROS_INFO("\033[1;31msocket failed\033[0m");
        freeaddrinfo(ai);
        return -1;
    }

    if (bind(fd, ai->ai_addr, ai->ai_addrlen) != 0)
    {
        ROS_INFO("\033[1;31mbind failed\033[0m");
        freeaddrinfo(ai);
        close(fd);
        return -1;
    }

    if (listen(fd, 10) != 0)
    {
        ROS_INFO("\033[1;31mbind failed\033[0m");
        freeaddrinfo(ai);
        close(fd);
        return -1;
    }
    freeaddrinfo(ai);
    return fd;
}

void HandControllProgram::serveClient(int fd)
{
    char buffer[2];
    int l;

    while (1)
    {
        l = recv(fd, buffer, sizeof(buffer), 0);
        if (l == 0){
            ROS_INFO("Connection closed.");
            break;
        } else if (l < 0){
            ROS_INFO("Conccetion error number: %d", l);
            break;
        } else if (l < 2){
            ROS_INFO("Recieved uncomplete message: %s", buffer);
            continue;
        }

        processInput(buffer, l);
    }
    close(fd);
}

void HandControllProgram::processInput(char * buffer, int length){
    int8_t leftPercent, rightPercent;

    leftPercent = (int8_t) buffer[0];
    rightPercent = (int8_t) buffer[1];

    int leftSpeed = (double) leftPercent / 100.0 * MAX_SPEED;
    int rightSpeed = (double) rightPercent / 100.0 * MAX_SPEED;

    MotorManager::getInstance()->publishCoords(leftSpeed, rightSpeed);
}