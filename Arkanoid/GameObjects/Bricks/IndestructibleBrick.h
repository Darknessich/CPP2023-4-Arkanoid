#pragma once
#include "Brick.h"

class IndestructibleBrick : public Brick {
 public:
   IndestructibleBrick();
   IndestructibleBrick(PointF center, float width, float height, int health, Bonus* bonus);
   int getDamage(Ball* ball) override;
   void draw(GLFWwindow* window) const override;
};