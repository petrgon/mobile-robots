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

#define SEARCHING_TIME 3000
#define MOVE_FORWARD_TIME 2000
#define COLLISION_TIME 450

class CatchPuckProgram : public Program
{
public:
  CatchPuckProgram(int irFrequency);
  CatchPuckProgram(const CatchPuckProgram &) = default;
  CatchPuckProgram(CatchPuckProgram &&) = default;

  virtual CatchPuckProgram &operator=(const CatchPuckProgram &) = default;
  virtual CatchPuckProgram &operator=(CatchPuckProgram &&) = default;

  virtual bool operator==(const CatchPuckProgram &b) const;

  virtual void puckAquiredEventHandler() override;

private:
  int irFrequency;
};
#endif /*CATCH_PUCK_PROGRAM_H*/