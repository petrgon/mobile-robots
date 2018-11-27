#ifndef SCORE_PROGRAM_H
#define SCORE_PROGRAM_H

#include "program.h"
#include "../managers/program_manager.h"
#include "catch_puck_program.h"
#include "../states/search_left_state.h"
#include "../states/move_forward_state.h"
#include "../states/move_back_left_state.h"
#include "../states/move_back_right_state.h"
#include "../states/move_backward_state.h"
#include <atomic>

#define SEARCHING_TIME 3000
#define MOVE_FORWARD_TIME 2000
#define COLLISION_TIME 450

class ScoreProgram : public Program
{
public:
  ScoreProgram(int irFreqency);
  ScoreProgram(const ScoreProgram &) = default;
  ScoreProgram(ScoreProgram &&) = default;

  virtual ScoreProgram &operator=(const ScoreProgram &) = default;
  virtual ScoreProgram &operator=(ScoreProgram &&) = default;

  virtual bool operator==(const ScoreProgram &b) const;

  virtual void puckLostEventHandler() override;

private:
  int irFrequency;
};
#endif /*SCORE_PROGRAM_H*/