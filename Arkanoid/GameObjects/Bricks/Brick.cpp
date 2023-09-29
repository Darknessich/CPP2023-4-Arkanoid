#include "Brick.h"
#include "../../GameSettings.h"

Brick::Brick()
  : Colliding(), p1(), p2(), health(0), bonus(nullptr)
{}

Brick::Brick(PointF center, float width, float height, int health, Bonus* bonus)
  : Colliding(center, width, height), p1({ center.x - width / 2.0f, center.y - height / 2.0f }),
  p2({ center.x + width / 2.0f, center.y + height / 2.0f }), health(health), bonus(bonus)
{}

void Brick::draw(GLFWwindow* window) const {
  int width, height;
  glfwGetFramebufferSize(window, &width, &height);
  RectF rect = Colliding::getRect();

  float kx = 2.f / width;
  float ky = 2.f / height;
  rect.p1.x *= kx;
  rect.p2.x *= kx;
  rect.p1.y *= ky;
  rect.p2.y *= ky;

  glBegin(GL_QUADS);
  glColor3f(GS::GO::Bricks::Brick::color3f[0], GS::GO::Bricks::Brick::color3f[1], GS::GO::Bricks::Brick::color3f[2]);
  glVertex3f(rect.p1.x, rect.p1.y, 0.f);
  glVertex3f(rect.p1.x, rect.p2.y, 0.f);
  glVertex3f(rect.p2.x, rect.p2.y, 0.f);
  glVertex3f(rect.p2.x, rect.p1.y, 0.f);
  glEnd();

  glBegin(GL_LINE_LOOP);
  glColor3f(1.2f * GS::GO::Bricks::Brick::color3f[0],
    1.2f * GS::GO::Bricks::Brick::color3f[1], 1.2f * GS::GO::Bricks::Brick::color3f[2]);
  glVertex3f(rect.p1.x, rect.p1.y, 0.f);
  glVertex3f(rect.p1.x, rect.p2.y, 0.f);
  glVertex3f(rect.p2.x, rect.p2.y, 0.f);
  glVertex3f(rect.p2.x, rect.p1.y, 0.f);
  glEnd();

  Colliding::draw(window);
}

bool Brick::collided(Colliding const* other, VectorF& direction) {
  if (!Colliding::collided(other, direction))
    return false;

  p1.x += direction.x;
  p1.y += direction.y;
  p2.x += direction.x;
  p2.y += direction.y;
  Colliding::moveOn(direction);
  return true;
}

void Brick::moveOn(VectorF const& direction) {
  p1 += direction;
  p2 += direction;
  Colliding::moveOn(direction);
}

int Brick::getDamage(Ball* ball) {
  return health -= ball->getDamage();
}

int Brick::getHealth() {
  return health;
}

Bonus* Brick::dropBonus() const {
  if (bonus) bonus->drop(0.5f * (p1 + p2));
  return bonus;
}