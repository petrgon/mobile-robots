#ifndef MOVE_SEARCH_LEFT_STATE_H
#define MOVE_SEARCH_LEFT_STATE_H

#include "state.h"
#include "../managers/motor_manager.h"

#define SPEED_LEFT -95
#define SPEED_RIGHT 100

class SearchLeftState : public State
{
public:
  SearchLeftState(Program *);
  SearchLeftState(Program *, int);
  SearchLeftState(const SearchLeftState &) = default;
  SearchLeftState(SearchLeftState &&) = default;

  virtual ~SearchLeftState() = 0;

  virtual SearchLeftState &operator=(const SearchLeftState &) = default;
  virtual SearchLeftState &operator=(SearchLeftState &&) = default;

  virtual bool operator==(const SearchLeftState &b) const;

  virtual void run() override;
  virtual void stateInit() override;
};
#endif /*MOVE_SEARCH_LEFT_STATE_H*/