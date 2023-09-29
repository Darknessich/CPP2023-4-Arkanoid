#pragma once
#include "Moving.h"

class Ball : public Moving {
public:
  Ball(PointF p0, float radius, VectorF speed, int damage);

  bool collided(Colliding const* other, VectorF& direction) override;
  void moveOn(VectorF const& direction) override;
  void draw(GLFWwindow* window) const override;
  void update(float dt) override;

  int getDamage() const;
  void accelerate(float accel);
private:
  VectorF speed;
  float radius;
  int damage;
};