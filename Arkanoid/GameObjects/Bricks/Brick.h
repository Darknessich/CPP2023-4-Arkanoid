#pragma once
#include "../../Engine/Physics/Colliding.h"
#include "../Ball.h"
#include "../Bonus/Bonus.h"

class Brick : public virtual Colliding {
public:
  Brick();
  Brick(PointF center, float width, float height, int health, Bonus* bonus);

  void draw(GLFWwindow* window) const override;
  bool collided(Colliding const* other, VectorF& direction) override;
  void moveOn(VectorF const& direction) override;

  virtual int getDamage(Ball* ball);
  Bonus* dropBonus() const;
  int getHealth();

protected:
  PointF p1, p2;
  int health;
private:
  Bonus* bonus;
};