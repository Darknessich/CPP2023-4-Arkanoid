#include "Carriage.h"
#include "../GameSettings.h"

#define M_PI 3.14159265f
#include <cmath>
#include <cstdlib>
#include <algorithm>

float random() {
  return rand() / (RAND_MAX + 1.f);
}

Carriage::Carriage(PointF center, float width, float height, float maxSpeed, int balls)
  : Colliding(center, width, height), Moving(), direction(EDirections::D_NONE),
  speed(0.0f), maxSpeed(maxSpeed), balls(balls)
{
}

void Carriage::SetDirection(EDirections dir) {
  direction = dir;
}

Carriage::EDirections Carriage::GetDirection() const{
  return direction;
}

void Carriage::draw(GLFWwindow* window) const {
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
  glColor3f(GS::Win::color3f[0], GS::Win::color3f[1], GS::Win::color3f[2]);
  glVertex3f(rect.p1.x, rect.p1.y, 0.f);
  glVertex3f(rect.p1.x, rect.p2.y, 0.f);
  glVertex3f(rect.p2.x, rect.p2.y, 0.f);
  glVertex3f(rect.p2.x, rect.p1.y, 0.f);
  glEnd();

  glBegin(GL_LINE_LOOP);
  glColor3f(1.2f * GS::Win::color3f[0],
    1.2f * GS::Win::color3f[1], 1.2f * GS::Win::color3f[2]);
  glVertex3f(rect.p1.x, rect.p1.y, 0.f);
  glVertex3f(rect.p1.x, rect.p2.y, 0.f);
  glVertex3f(rect.p2.x, rect.p2.y, 0.f);
  glVertex3f(rect.p2.x, rect.p1.y, 0.f);
  glEnd();

  if (balls) {
    Ball* tmp = new Ball(
      Colliding::center() +
      PointF(0.f, 0.5f * Colliding::height() + GS::GO::Ball::radius),
      GS::GO::Ball::radius, { 0.f, 0.f }, 0);

    tmp->draw(window);
    delete tmp;
  }

  Colliding::draw(window);
}

bool Carriage::collided(Colliding const* other, VectorF& direction) {
  if (!Colliding::collided(other, direction))
    return false;

  Colliding::moveOn(direction);
  return true;
}

void Carriage::moveOn(VectorF const& direction) {
  Colliding::moveOn(direction);
}

void Carriage::update(float dt) {
  speed = maxSpeed * static_cast<float>(direction);
  Colliding::moveOn({ speed * dt, 0.f });
}

void Carriage::addBall() {
  balls++;
}

void Carriage::deleteBall() {
  balls--;
}

Ball* Carriage::spawnBall() {
  if (balls <= 0)
    return nullptr;

  deleteBall();
  float alpha = M_PI * (5.f * random() / 6.f + 1.f / 12.f);
  return new Ball(
    Colliding::center() + 
    PointF(0.f, Colliding::height() / 2.f + GS::GO::Ball::radius), 
    GS::GO::Ball::radius, 
    { GS::GO::Ball::baseSpeed * cos(alpha), 
    GS::GO::Ball::baseSpeed * sin(alpha)}, 
    GS::GO::Ball::damage);
}

void Carriage::rewidth(float delta) {
  float width = delta + Colliding::width();

  if (width > GS::GO::Carriage::maxWidth)
    delta += GS::GO::Carriage::maxWidth - width;

  if (width < GS::GO::Carriage::minWidth)
    delta += GS::GO::Carriage::minWidth - width;

  Colliding::resize({delta, 0.0});
}