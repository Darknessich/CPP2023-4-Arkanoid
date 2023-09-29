#pragma once

#include "Effect.h"

class Slowdown : public Effect {
  void start(Game* game) override;
  void end(Game* game) override;
  void draw(GLFWwindow* window) const override;
};