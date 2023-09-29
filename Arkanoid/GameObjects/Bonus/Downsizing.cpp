#include "Downsizing.h"
#include "../../GameSettings.h"
#include "../../game.h"

void Downsizing::start(Game* game) {
  game->rewidthCarriage(-40.f);
  time = GS::GO::Bonus::time;
}

void Downsizing::end(Game* game) {
  game->rewidthCarriage(+40.f);
}

void Downsizing::draw(GLFWwindow* window) const {
  int width, height;
  glfwGetFramebufferSize(window, &width, &height);
  PointF center = Colliding::center();
  float dx = GS::GO::Bonus::width / 2.f;
  float dy = GS::GO::Bonus::height / 6.f;
  RectF rect({ center - PointF(dx, dy), center + PointF(dx,dy) });

  float kx = 2.f / width;
  float ky = 2.f / height;
  rect.p1.x *= kx;
  rect.p2.x *= kx;
  rect.p1.y *= ky;
  rect.p2.y *= ky;

  glBegin(GL_QUADS);
  glColor3f(GS::GO::Bonus::Accel::color3f[0], GS::GO::Bonus::Accel::color3f[1], GS::GO::Bonus::Accel::color3f[2]);
  glVertex3f(rect.p1.x, rect.p1.y, 0.f);
  glVertex3f(rect.p1.x, rect.p2.y, 0.f);
  glVertex3f(rect.p2.x, rect.p2.y, 0.f);
  glVertex3f(rect.p2.x, rect.p1.y, 0.f);
  glEnd();

  glBegin(GL_LINE_LOOP);
  glColor3f(0.5f * GS::GO::Bonus::Accel::color3f[0],
    0.5f * GS::GO::Bonus::Accel::color3f[1], 0.5f * GS::GO::Bonus::Accel::color3f[2]);
  glVertex3f(rect.p1.x, rect.p1.y, 0.f);
  glVertex3f(rect.p1.x, rect.p2.y, 0.f);
  glVertex3f(rect.p2.x, rect.p2.y, 0.f);
  glVertex3f(rect.p2.x, rect.p1.y, 0.f);
  glEnd();
}