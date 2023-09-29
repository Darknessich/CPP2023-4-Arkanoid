#include "IncreaseSize.h"
#include "../../GameSettings.h"
#include "../../game.h"

void IncreaseSize::start(Game* game) {
  game->rewidthCarriage(160.f);
  time = GS::GO::Bonus::time;
}

void IncreaseSize::end(Game* game) {
  game->rewidthCarriage(-160.f);
}

void IncreaseSize::draw(GLFWwindow* window) const {
  int width, height;
  glfwGetFramebufferSize(window, &width, &height);
  PointF center = Colliding::center();
  float dx = GS::GO::Bonus::width / 2.f;
  float dy = GS::GO::Bonus::height / 2.f;
  PointF delta(dx, dy);
  RectF rect1({ center - delta, center + delta });
  delta *= 0.3f;
  RectF rect2({ center - delta, center + delta });

  float kx = 2.f / width;
  float ky = 2.f / height;
  rect1.p1.x *= kx;
  rect1.p2.x *= kx;
  rect1.p1.y *= ky;
  rect1.p2.y *= ky;

  rect2.p1.x *= kx;
  rect2.p2.x *= kx;
  rect2.p1.y *= ky;
  rect2.p2.y *= ky;

  glBegin(GL_POLYGON);
  glColor3f(GS::GO::Bricks::Save::color3f[0], GS::GO::Bricks::Save::color3f[1], GS::GO::Bricks::Save::color3f[2]);
  glVertex3f(rect1.p1.x, rect2.p1.y, 0.f);
  glVertex3f(rect1.p1.x, rect2.p2.y, 0.f);
  glVertex3f(rect2.p1.x, rect2.p2.y, 0.f);
  glVertex3f(rect2.p1.x, rect1.p2.y, 0.f);
  glVertex3f(rect2.p2.x, rect1.p2.y, 0.f);
  glVertex3f(rect2.p2.x, rect2.p2.y, 0.f);
  glVertex3f(rect1.p2.x, rect2.p2.y, 0.f);
  glVertex3f(rect1.p2.x, rect2.p1.y, 0.f);
  glVertex3f(rect2.p2.x, rect2.p1.y, 0.f);
  glVertex3f(rect2.p2.x, rect1.p1.y, 0.f);
  glVertex3f(rect2.p1.x, rect1.p1.y, 0.f);
  glVertex3f(rect2.p1.x, rect2.p1.y, 0.f);
  glVertex3f(rect1.p1.x, rect2.p1.y, 0.f);
  glEnd();

  glBegin(GL_LINE_LOOP);
  glColor3f(1.5f * GS::GO::Bricks::Save::color3f[0],
    1.5f * GS::GO::Bricks::Save::color3f[1], 1.5f * GS::GO::Bricks::Save::color3f[2]);
  glVertex3f(rect1.p1.x, rect2.p1.y, 0.f);
  glVertex3f(rect1.p1.x, rect2.p2.y, 0.f);
  glVertex3f(rect2.p1.x, rect2.p2.y, 0.f);
  glVertex3f(rect2.p1.x, rect1.p2.y, 0.f);
  glVertex3f(rect2.p2.x, rect1.p2.y, 0.f);
  glVertex3f(rect2.p2.x, rect2.p2.y, 0.f);
  glVertex3f(rect1.p2.x, rect2.p2.y, 0.f);
  glVertex3f(rect1.p2.x, rect2.p1.y, 0.f);
  glVertex3f(rect2.p2.x, rect2.p1.y, 0.f);
  glVertex3f(rect2.p2.x, rect1.p1.y, 0.f);
  glVertex3f(rect2.p1.x, rect1.p1.y, 0.f);
  glVertex3f(rect2.p1.x, rect2.p1.y, 0.f);
  glEnd();
}