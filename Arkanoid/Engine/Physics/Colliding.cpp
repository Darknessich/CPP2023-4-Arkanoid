#include "Colliding.h"
#include "../../GameSettings.h"

Colliding::Colliding() 
  : m_box({ 0.f, 0.f }, { 0.f, 0.f }), m_center({0.f, 0.f}), m_width(0), m_height(0)
{}

Colliding::Colliding(PointF const center, float width, float height)
  : m_box(center - PointF(width / 2.f, height / 2.f),
    center + PointF(width / 2.f, height / 2.f)), 
  m_center(center), m_width(width), m_height(height)
{
}

void Colliding::moveTo(PointF const& p) {
  m_center = p;
  m_box.move(p);
}

void Colliding::moveOn(VectorF const& direction) {
  m_center += direction;
  m_box.moveOn(direction);
}

void Colliding::resize(VectorF const& delta) {
  m_width += delta.x;
  m_height += delta.y;
  m_box.resize(delta);
}

bool Colliding::out(Colliding const* other) const {
  return m_box.outBox(other->m_box);
}

bool Colliding::in(Colliding const* other) const {
  return m_box.inBox(other->m_box);
}

RectF Colliding::getRect() const {
  return m_box.getRect();
}

PointF Colliding::center() const {
  return m_center;
}

float Colliding::width() const {
  return m_width;
}

float Colliding::height() const {
  return m_height;
}

void Colliding::draw(GLFWwindow* window) const {
  if (GS::drawHitbox)
    m_box.draw(window);
}

bool Colliding::collided(Colliding const* other, VectorF& direction) {
  direction = m_box.interspect(other->m_box);
  return direction.x != 0 || direction.y != 0;
}

