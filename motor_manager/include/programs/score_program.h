#ifndef SCORE_PROGRAM_H
#define SCORE_PROGRAM_H

#include "program.h"
#include "../managers/program_manager.h"
#include "catch_puck_program.h"
#include "../states/search_left_state.h"
#include "../states/search_right_state.h"
#include "../states/move_forward_state.h"
#include "../states/move_state.h"
#include "../states/move_back_left_state.h"
#include "../states/move_back_right_state.h"
#include "../states/move_backward_state.h"
#include <atomic>

class ScoreProgram : public Program
{
public:
  ScoreProgram(int irFrequency);
  ScoreProgram(const ScoreProgram &) = default;
  ScoreProgram(ScoreProgram &&) = default;

  virtual ~ScoreProgram() override;

  virtual ScoreProgram &operator=(const ScoreProgram &) = default;
  virtual ScoreProgram &operator=(ScoreProgram &&) = default;

  virtual void lightLostEventHandler() override;

private:
  int irFrequency;

  static const int SEARCHING_TIME = 4500;
  static const int TURN_TIME = 550;
  static const int MOVE_FORWARD_TIME = 1800;
  static const int COLLISION_TIME = 750;
};
#endif /*SCORE_PROGRAM_H*/
