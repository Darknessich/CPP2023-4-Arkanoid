#pragma once
#include "../Moving.h"
#include "Brick.h"

class MovingBrick : public Brick, public Moving {
public:
  MovingBrick(PointF center, float width, float height, int health, Bonus* bonus, VectorF speed);

  void draw(GLFWwindow* window) const override;
  bool collided(Colliding const* other, VectorF& direction) override;
  void moveOn(VectorF const& direction) override;
  void update(float dt) override;
private:
  VectorF speed;
};