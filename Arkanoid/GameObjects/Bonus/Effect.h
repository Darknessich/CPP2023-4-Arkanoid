#pragma once
#include "../Moving.h"

class Game;

class Effect : public Moving {
public:
  virtual void start(Game* game) = 0;
  virtual void end(Game* game) = 0;
  void update(float dt) override;
  
  float timeLeft() const;
protected:
  float time;
};