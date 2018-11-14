#ifndef GET_PUCK_STATE_MANAGER_H
#define GET_PUCK_STATE_MANAGER_H

#include "state.h"
#include "../managers/motor_manager.h"
#include "../managers/sensor_manager.h"
#include "../managers/callback_time_manager.h"
#include <vector>

class GetPuckState : public State
{
public:
  GetPuckState();
  ~GetPuckState() override;

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

private:
  enum Actions {
    SEARCH_LEFT, SEARCH_RIGHT, MOVE_FORWARD
  };

  bool timeIsUp;
  bool puckTouchTriggered;
  bool lightDetected;
  bool leftTouchTriggered;
  bool rightTouchTriggered;

  Actions nextAction;
};
#endif /*GET_PUCK_STATE_MANAGER_H*/