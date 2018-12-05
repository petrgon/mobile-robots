#ifndef CATCH_PUCK_PROGRAM_H
#define CATCH_PUCK_PROGRAM_H

#include "program.h"
#include "../managers/program_manager.h"
#include "score_program.h"
#include "../states/search_left_state.h"
#include "../states/search_right_state.h"
#include "../states/move_forward_state.h"
#include "../states/move_back_left_state.h"
#include "../states/move_back_right_state.h"
#include "../states/move_backward_state.h"
#include <atomic>

class CatchPuckProgram : public Program
{
public:
  CatchPuckProgram(int irFrequency);
  CatchPuckProgram(const CatchPuckProgram &) = default;
  CatchPuckProgram(CatchPuckProgram &&) = default;

  virtual ~CatchPuckProgram() override;

  virtual CatchPuckProgram &operator=(const CatchPuckProgram &) = default;
  virtual CatchPuckProgram &operator=(CatchPuckProgram &&) = default;

  virtual void puckAquiredEventHandler() override;

private:
  int irFrequency;

  static const int SPEED = 100;
  static const int SEARCHING_TIME = 3500;
  static const int MOVE_FORWARD_TIME = 1800;
  static const int COLLISION_TIME = 850;
};
#endif /*CATCH_PUCK_PROGRAM_H*/
