#ifndef MOVE_SEARCH_RIGHT_STATE_H
#define MOVE_SEARCH_RIGHT_STATE_H

#include "state.h"
#include "../managers/motor_manager.h"

#define SPEED_LEFT 100
#define SPEED_RIGHT -95

class SearchRightState : public State
{
public:
  SearchRightState(Program *);
  SearchRightState(Program *, int);
  SearchRightState(const SearchRightState &) = default;
  SearchRightState(SearchRightState &&) = default;

  virtual ~SearchRightState();

  virtual SearchRightState &operator=(const SearchRightState &) = default;
  virtual SearchRightState &operator=(SearchRightState &&) = default;

  virtual bool operator==(const SearchRightState &b) const;

  virtual void run() override;
  virtual void stateInit() override;
};
#endif /*MOVE_SEARCH_RIGHT_STATE_H*/