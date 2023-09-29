#include "AccelBrick.h"
#include "../../GameSettings.h"

AccelBrick::AccelBrick()
  : Colliding(), Brick(), accel(1.0f)
{}

AccelBrick::AccelBrick(PointF center, float width, float height, int health, Bonus* bonus, float accel)
  : Colliding(center, width, height), Brick(center, width, height, health, bonus), accel(accel)
{}

int AccelBrick::getDamage(Ball* ball) {
  ball->accelerate(accel);
  return Brick::getDamage(ball);
}

void AccelBrick::draw(GLFWwindow* window)  const {
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
  glColor3f(GS::GO::Bricks::Accel::color3f[0], GS::GO::Bricks::Accel::color3f[1], GS::GO::Bricks::Accel::color3f[2]);
  glVertex3f(rect.p1.x, rect.p1.y, 0.f);
  glVertex3f(rect.p1.x, rect.p2.y, 0.f);
  glVertex3f(rect.p2.x, rect.p2.y, 0.f);
  glVertex3f(rect.p2.x, rect.p1.y, 0.f);
  glEnd();

  glBegin(GL_LINE_LOOP);
  glColor3f(1.2f * GS::GO::Bricks::Accel::color3f[0],
    1.2f * GS::GO::Bricks::Accel::color3f[1], 1.2f * GS::GO::Bricks::Accel::color3f[2]);
  glVertex3f(rect.p1.x, rect.p1.y, 0.f);
  glVertex3f(rect.p1.x, rect.p2.y, 0.f);
  glVertex3f(rect.p2.x, rect.p2.y, 0.f);
  glVertex3f(rect.p2.x, rect.p1.y, 0.f);
  glEnd();

  Colliding::draw(window);
}