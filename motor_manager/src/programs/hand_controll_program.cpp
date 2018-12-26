#include "../../include/programs/hand_controll_program.h"

HandControllProgram::HandControllProgram() : Program()
{
    srvFd = createServerFd(IP_ADDRESS, PORT); // TODO change IP and port
    if (srvFd == -1)
    {
        ROS_INFO("Enable to create server.");
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
    while (1)
    {
        struct sockaddr sa;
        socklen_t saSize = sizeof(sa);
        int cliFd = accept(srvFd, &sa, &saSize);
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
        ROS_INFO("getaddrinfo failed");
        return -1;
    }

    fd = socket(ai->ai_family, SOCK_STREAM, 0);
    if (fd == -1)
    {
        ROS_INFO("socket failed");
        freeaddrinfo(ai);
        return -1;
    }

    if (bind(fd, ai->ai_addr, ai->ai_addrlen) != 0)
    {
        ROS_INFO("bind failed");
        freeaddrinfo(ai);
        close(fd);
        return -1;
    }

    if (listen(fd, 10) != 0)
    {
        ROS_INFO("bind failed");
        freeaddrinfo(ai);
        close(fd);
        return -1;
    }
    freeaddrinfo(ai);
    return fd;
}

void HandControllProgram::serveClient(int fd)
{
    char buffer[100];
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
        }

        processInput(buffer, l);
    }
    close(fd);
}

void HandControllProgram::processInput(char * buffer, int length){
    int leftPercent, rightPercent;

    std::size_t indx;

    leftPercent = std::stoi(buffer, &indx);
    rightPercent = std::stoi(buffer + indx);

    int leftSpeed = (double) leftPercent / 100.0 * MAX_SPEED;
    int rightSpeed = (double) rightPercent / 100.0 * MAX_SPEED;

    MotorManager::getInstance()->publishCoords(leftSpeed, rightSpeed);
}