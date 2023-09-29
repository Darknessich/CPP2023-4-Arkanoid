#pragma once
#include "Brick.h"

class AccelBrick : public Brick {
public:
  AccelBrick();
  AccelBrick(PointF center, float width, float height, int health, Bonus* bonus, float accel);
  int getDamage(Ball* ball) override;
  void draw(GLFWwindow*) const override;
private:
  float accel;
};