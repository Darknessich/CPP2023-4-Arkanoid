#define M_PI 3.14159265f
#include <cmath>

#include "../GameSettings.h"
#include "Ball.h"

Ball::Ball(PointF p0, float radius, VectorF speed, int damage)
  : Colliding(p0, 2.f * radius, 2.f * radius), Moving(),
  speed(speed), radius(radius), damage(damage)
{}

bool Ball::collided(Colliding const* other, VectorF& direction) {
  if (!Colliding::collided(other, direction))
    return false;

  Colliding::moveOn(2.f * direction);

  speed.x = direction.x == 0.0f ? speed.x :
    direction.x > 0.0f ? std::abs(speed.x) : -std::abs(speed.x);

  speed.y = direction.y == 0.0f ? speed.y :
    direction.y > 0.0f ? std::abs(speed.y) : -std::abs(speed.y);

  return true;
}

void Ball::moveOn(VectorF const& direction) {
  Colliding::moveOn(direction);
}

void Ball::draw(GLFWwindow* window) const {
  int width, height;
  glfwGetFramebufferSize(window, &width, &height);
  PointF center = Colliding::center();

  float rx = 2.0f * radius / width;
  float ry = 2.0f * radius / height;
  float x = 2.0f * center.x / width;
  float y = 2.0f * center.y / height;

  int steps = 25;
  glBegin(GL_TRIANGLE_FAN);
  glColor3f(GS::GO::Ball::color3f[0], GS::GO::Ball::color3f[1], GS::GO::Ball::color3f[2]);
  glVertex3f(x, y, 0.0f);
  for (int i = 0; i < steps; i++) {
    float angle = i * 2.0f * M_PI / (steps - 1);
    glVertex3f(x + rx * cosf(angle), y + ry * sinf(angle), 0.0f);
  }
  glEnd();

  glBegin(GL_LINE_LOOP);
  glColor3f(0.5f * GS::GO::Ball::color3f[0],
    0.5f * GS::GO::Ball::color3f[1], 0.5f * GS::GO::Ball::color3f[2]);
  for (int i = 0; i < steps; i++) {
    float angle = i * 2.0f * M_PI / (steps - 1);
    glVertex3f(x + rx * cosf(angle), y + ry * sinf(angle), 0.0f);
  }
  glEnd();

  Colliding::draw(window);
}

void Ball::update(float dt) {
  Colliding::moveOn(dt * this->speed);
}

int Ball::getDamage() const {
  return this->damage;
}

void Ball::accelerate(float accel) {
  speed *= accel;

  float speedNorm = speed.x * speed.x + speed.y * speed.y;
  if (speedNorm > GS::GO::Ball::maxSpeed * GS::GO::Ball::maxSpeed)
    speed *= std::sqrt(GS::GO::Ball::maxSpeed / speedNorm);
}