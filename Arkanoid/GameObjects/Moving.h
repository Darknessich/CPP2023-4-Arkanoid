#pragma once
#include "../Engine/Physics/Colliding.h"

class Moving : public virtual Colliding {
public:
  using Colliding::Colliding;
  virtual void update(float dt) = 0;
};