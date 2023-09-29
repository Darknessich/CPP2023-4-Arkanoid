#include "Bonus.h"
#include "../../GameSettings.h"

Bonus::Bonus(Effect* effect) 
  : Colliding({0.f, 0.f}, GS::GO::Bonus::width, GS::GO::Bonus::height), Moving(), effect(effect)
{}

Bonus* Bonus::drop(PointF center) {
  Colliding::moveTo(center);
  effect->moveTo(Colliding::center());
  return this;
}

void Bonus::kill() {
  delete effect;
  effect = nullptr;
}

Effect* Bonus::dropEffect() {
  return effect;
}

void Bonus::draw(GLFWwindow* window) const {
  effect->draw(window);
  Colliding::draw(window);
}

void Bonus::update(float dt) {
  Colliding::moveOn({ 0.0f, GS::GO::Bonus::speed * dt });
  effect->moveTo(Colliding::center());
}