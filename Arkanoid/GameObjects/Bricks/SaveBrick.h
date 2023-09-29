#pragma once
#include "Brick.h"

class SaveBrick : public Brick {
public:
  SaveBrick(PointF center, float width, float height, int health);

  void draw(GLFWwindow* window) const override;
  int addHeal(int heal);
};