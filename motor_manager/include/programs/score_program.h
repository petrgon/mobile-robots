#ifndef SCORE_PROGRAM_H
#define SCORE_PROGRAM_H

#include "program.h"
#include "../states/state.h"
#include <atomic>

class ScoreProgram : public Program
{
public:
  ScoreProgram();
  ScoreProgram(const ScoreProgram &) = default;
  ScoreProgram(ScoreProgram &&) = default;

  virtual ScoreProgram &operator=(const ScoreProgram &) = default;
  virtual ScoreProgram &operator=(ScoreProgram &&) = default;

  virtual bool operator==(const ScoreProgram &b) const;
};

enum ScoreProgramStates : int
{
  MOVE_FORWARD_LEFT = 0,
  MOVE_FORWARD_RIGHT,
  SEARCH_LEFT
  //TODO add all states
};
#endif /*SCORE_PROGRAM_H*/