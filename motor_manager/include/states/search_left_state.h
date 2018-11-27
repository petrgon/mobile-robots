#ifndef MOVE_SEARCH_LEFT_STATE_H
#define MOVE_SEARCH_LEFT_STATE_H

#include "state.h"
#include "../managers/motor_manager.h"

class SearchLeftState : public State
{
public:
  SearchLeftState(Program *);
  SearchLeftState(Program *, int);
  SearchLeftState(const SearchLeftState &) = default;
  SearchLeftState(SearchLeftState &&) = default;

  virtual SearchLeftState &operator=(const SearchLeftState &) = default;
  virtual SearchLeftState &operator=(SearchLeftState &&) = default;

  virtual bool operator==(const SearchLeftState &b) const;

  virtual void run() override;
  virtual void stateInit() override;

private:
  static const int SPEED_LEFT = -95;
  static const int SPEED_RIGHT = 100;
};
#endif /*MOVE_SEARCH_LEFT_STATE_H*/