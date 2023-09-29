#define M_PI 3.14159265f
#include <cmath>

#include "Accelerate.h"
#include "../../GameSettings.h"
#include "../../game.h"

void Accelerate::start(Game* game) {
  game->accelerateBall(GS::GO::Bonus::Accel::accel);
  time = GS::GO::Bonus::time;
}

void Accelerate::end(Game* game) {
  game->accelerateBall(1.f / GS::GO::Bonus::Accel::accel);
}

void Accelerate::draw(GLFWwindow* window) const {
  int width, height;
  glfwGetFramebufferSize(window, &width, &height);
  PointF center = Colliding::center();
  float radius = GS::GO::Ball::radius;

  float rx = 2.0f * radius / width;
  float ry = 2.0f * radius / height;
  float x = 2.0f * center.x / width;
  float y = 2.0f * center.y / height;

  int steps = 25;
  glBegin(GL_TRIANGLE_FAN);
  glColor3f(GS::GO::Bonus::Accel::color3f[0], GS::GO::Bonus::Accel::color3f[1], GS::GO::Bonus::Accel::color3f[2]);
  glVertex3f(x, y, 0.0f);
  for (int i = 0; i < steps; i++) {
    float angle = i * 2.0f * M_PI / (steps - 1);
    glVertex3f(x + rx * cosf(angle), y + ry * sinf(angle), 0.0f);
  }
  glEnd();

  glBegin(GL_LINE_LOOP);
  glColor3f(0.5f * GS::GO::Bonus::Accel::color3f[0],
    0.5f * GS::GO::Bonus::Accel::color3f[1], 0.5f * GS::GO::Bonus::Accel::color3f[2]);
  for (int i = 0; i < steps; i++) {
    float angle = i * 2.0f * M_PI / (steps - 1);
    glVertex3f(x + rx * cosf(angle), y + ry * sinf(angle), 0.0f);
  }
  glEnd();
}