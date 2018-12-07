#ifndef GET_PUCK_PROGRAM_MANAGER_H
#define GET_PUCK_PROGRAM_MANAGER_H

#include "program.h"
#include "../managers/motor_manager.h"
#include "../managers/sensor_manager.h"
#include "../managers/callback_time_manager.h"
#include <vector>
#include <atomic>
#include <string>

class HockeyProgram : public Program
{
public:
  HockeyProgram();
  ~HockeyProgram() override;

  void run() override;

  void timeElapsedEventHandler() override;

  void puckAquiredEventHandler() override;
  void puckLostEventHandler() override;

  void lightDetectedEventHandler() override;
  void lightLostEventHandler() override;

  void leftTouchTriggeredEventHandler() override;
  void leftTouchFreedEventHandler() override;

  void rightTouchTriggeredEventHandler() override;
  void rightTouchFreedEventHandler() override;

  void bothTouchTriggeredEventHandler() override;
  void bothTouchFreedEventHandler() override;

  virtual std::string getName() override;

private:
  enum Actions {
    SEARCH_LEFT, SEARCH_RIGHT, MOVE_FORWARD_LEFT, MOVE_FORWARD_RIGHT, PUCK_TRIGGERED, 
    LEFT_TRIGGERED, RIGHT_TRIGGERED, BOTH_TRIGGERED, LIGHT_DETECTED
  };

  void doAction(int leftWheelSpeed, int rightWheelSpeed, Actions nextAction, int timeOut);

  std::atomic<bool> timeIsUp;
  bool puckTouchTriggered;
  bool lightDetected;
  bool leftTouchTriggered;
  bool rightTouchTriggered;

  Actions actualAction;
};
#endif /*GET_PUCK_PROGRAM_MANAGER_H*/
