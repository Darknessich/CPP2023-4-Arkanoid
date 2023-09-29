#include "Effect.h"

void Effect::update(float dt) {
  time -= dt;
}

float Effect::timeLeft() const {
  return time;
}