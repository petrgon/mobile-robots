#ifndef HAND_CONTROLL_PROGRAM_H
#define HAND_CONTROLL_PROGRAM_H

#include "program.h"
#include "../managers/program_manager.h"
#include "../managers/motor_manager.h"
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <atomic>
#include <string>

class HandControllProgram : public Program
{
  public:
    HandControllProgram();
    HandControllProgram(const HandControllProgram &) = default;
    HandControllProgram(HandControllProgram &&) = default;

    virtual ~HandControllProgram() override;

    virtual HandControllProgram &operator=(const HandControllProgram &) = default;
    virtual HandControllProgram &operator=(HandControllProgram &&) = default;

    virtual std::string getName() override;

    virtual void run() override;

  private:
    int createServerFd(const char *, int);
    void serveClient(int);
    void processInput(char *, int);

    int srvFd;
    static const int PORT = 6072;
    static constexpr const char * IP_ADDRESS = "localhost";
    static const int MAX_SPEED = 240;
    
};
#endif /*HAND_CONTROLL_PROGRAM_H*/
