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
#include "../states/program_timeout_state.h"
#include <atomic>

#define SEARCHING_TIME 3000
#define CURVE_TIME 3000
#define ROTATION_TIME 500
#define MOVE_FORWARD_TIME 4000
#define COLLISION_TIME 450

#define CURVE_LEFT_SPEED 100
#define CURVE_RIGHT_SPEED 110

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

private:
  int irFrequency;
};
#endif /*DIRECT_SEARCH_PUCK_PROGRAM_H*/