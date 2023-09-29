#pragma once
#include "../Engine/Physics/Colliding.h"

class Room : public Colliding {
public:
  using Colliding::Colliding;
  void draw(GLFWwindow* window) const override;
};