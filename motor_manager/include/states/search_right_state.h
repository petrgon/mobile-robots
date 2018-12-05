#ifndef MOVE_SEARCH_RIGHT_STATE_H
#define MOVE_SEARCH_RIGHT_STATE_H

#include "move_state.h"
#include "../managers/motor_manager.h"

class SearchRightState : public MoveState
{
public:
  SearchRightState(Program *);
  SearchRightState(Program *, int);
  SearchRightState(const SearchRightState &) = default;
  SearchRightState(SearchRightState &&) = default;

  virtual ~SearchRightState() override;

  virtual SearchRightState &operator=(const SearchRightState &) = default;
  virtual SearchRightState &operator=(SearchRightState &&) = default;

private:
  static const int SPEED_LEFT = 100;
  static const int SPEED_RIGHT = -100;
};
#endif /*MOVE_SEARCH_RIGHT_STATE_H*/
