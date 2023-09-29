#pragma once
#include "../Moving.h"
#include "Effect.h"

class Bonus : public Moving {
public:
  Bonus(Effect* effect);

  Bonus* drop(PointF center);
  void kill();
  Effect* dropEffect();

  void draw(GLFWwindow* window) const override;
  void update(float dt) override;
private:
  Effect* effect;
};