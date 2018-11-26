#ifndef MOVE_FORWARD_SCORE_STATE_H
#define MOVE_FORWARD_SCORE_STATE_H

#include "move_forward_state.h"
#include "../programs/score_program.h"

class MoveForwardScoreState : public MoveForwardState
{
public:
  MoveForwardScoreState(Program *);
  MoveForwardScoreState(const MoveForwardScoreState &) = default;
  MoveForwardScoreState(MoveForwardScoreState &&) = default;

  virtual ~MoveForwardScoreState();

  virtual MoveForwardScoreState &operator=(const MoveForwardScoreState &) = default;
  virtual MoveForwardScoreState &operator=(MoveForwardScoreState &&) = default;

  virtual bool operator==(const MoveForwardScoreState &b) const;
  
  virtual void timeElapsedEventHandler() override;

  virtual void puckAquiredEventHandler() override;
  virtual void puckLostEventHandler() override;

  virtual void lightDetectedEventHandler() override;
  virtual void lightLostEventHandler() override;

  virtual void leftTouchTriggeredEventHandler() override;
  virtual void leftTouchFreedEventHandler() override;

  virtual void rightTouchTriggeredEventHandler() override;
  virtual void rightTouchFreedEventHandler() override;

  virtual void bothTouchTriggeredEventHandler() override;
  virtual void bothTouchFreedEventHandler() override;

  virtual void ir600FoundEventHandler() override;
  virtual void ir600LostEventHandler() override;

  virtual void ir1500FoundEventHandler() override;
  virtual void ir1500LostEventHandler() override;

};
#endif /*MOVE_FORWARD_SCORE_STATE_H*/