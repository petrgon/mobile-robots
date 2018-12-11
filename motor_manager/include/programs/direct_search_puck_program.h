#ifndef DIRECT_SEARCH_PUCK_PROGRAM_H
#define DIRECT_SEARCH_PUCK_PROGRAM_H

#include "program.h"
#include "../managers/program_manager.h"
#include "score_program.h"
#include "catch_puck_program.h"
#include "../states/search_left_state.h"
#include "../states/search_right_state.h"
#include "../states/move_forward_state.h"
#include "../states/move_backward_state.h"
#include "../states/move_back_left_state.h"
#include "../states/program_timeout_state.h"
#include <atomic>
#include <string>

class DirectSearchPuckProgram : public Program
{
public:
  DirectSearchPuckProgram(int irFrequency);
  DirectSearchPuckProgram(const DirectSearchPuckProgram &) = default;
  DirectSearchPuckProgram(DirectSearchPuckProgram &&) = default;

  virtual ~DirectSearchPuckProgram() override;

  virtual DirectSearchPuckProgram &operator=(const DirectSearchPuckProgram &) = default;
  virtual DirectSearchPuckProgram &operator=(DirectSearchPuckProgram &&) = default;

  virtual void puckAquiredEventHandler() override;
  virtual void timeElapsedEventHandler() override;

  virtual std::string getName() override;

private:
  int irFrequency;

  static const int SEARCHING_TIME = 3800;
  static const int CURVE_TIME = 2500;
  static const int ROTATION_TIME = 500;
  static const int MOVE_FORWARD_TIME = 2500;
  static const int COLLISION_TIME = 900;

  static const int CURVE_LEFT_SPEED = 90;
  static const int CURVE_RIGHT_SPEED = 135;
};
#endif /*DIRECT_SEARCH_PUCK_PROGRAM_H*/
