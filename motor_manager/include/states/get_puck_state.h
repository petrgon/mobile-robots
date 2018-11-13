#ifndef GET_PUCK_STATE_MANAGER_H
#define GET_PUCK_STATE_MANAGER_H

#include "state.h"
#include "../managers/motor_manager.h"
#include <vector>

class GetPuckState : public State
{
public:
  GetPuckState();
  ~GetPuckState();

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

  Actions nextAction;
  
  bool lightDetected;
  bool leftTouchTriggered;
  bool rightTouchTriggered;
  bool puckTouchTriggered;
  bool timeIsUp;
};
#endif /*GET_PUCK_STATE_MANAGER_H*/