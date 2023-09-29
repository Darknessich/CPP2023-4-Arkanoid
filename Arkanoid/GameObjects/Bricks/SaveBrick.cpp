#include "SaveBrick.h"
#include "../../GameSettings.h"

SaveBrick::SaveBrick(PointF center, float width, float height, int health)
  : Colliding(center, width, height), Brick(center, width, height, health, nullptr)
{}

void SaveBrick::draw(GLFWwindow* window) const {
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
  glColor3f(GS::GO::Bricks::Save::color3f[0], GS::GO::Bricks::Save::color3f[1], GS::GO::Bricks::Save::color3f[2]);
  glVertex3f(rect.p1.x, rect.p1.y, 0.f);
  glVertex3f(rect.p1.x, rect.p2.y, 0.f);
  glVertex3f(rect.p2.x, rect.p2.y, 0.f);
  glVertex3f(rect.p2.x, rect.p1.y, 0.f);
  glEnd();

  glBegin(GL_LINE_LOOP);
  glColor3f(1.2f * GS::GO::Bricks::Save::color3f[0],
    1.2f * GS::GO::Bricks::Save::color3f[1], 1.2f * GS::GO::Bricks::Save::color3f[2]);
  glVertex3f(rect.p1.x, rect.p1.y, 0.f);
  glVertex3f(rect.p1.x, rect.p2.y, 0.f);
  glVertex3f(rect.p2.x, rect.p2.y, 0.f);
  glVertex3f(rect.p2.x, rect.p1.y, 0.f);
  glEnd();

  Colliding::draw(window);
}

int SaveBrick::addHeal(int heal) {
  return health += heal;
}