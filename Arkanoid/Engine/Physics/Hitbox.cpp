#include "Hitbox.h"

Hitbox::Hitbox(PointF const& p1, PointF const& p2)
  : Rendered(), rect({ p1, p2 })
{
}

void Hitbox::draw(GLFWwindow* window) const {
  int width, height;
  glfwGetFramebufferSize(window, &width, &height);

  PointF p1norm(0.0f, 0.0f), p2norm(0.0f, 0.0f);
  p1norm.x = 2.0f * rect.p1.x / width;
  p1norm.y = 2.0f * rect.p1.y / height;
  p2norm.x = 2.0f * rect.p2.x / width;
  p2norm.y = 2.0f * rect.p2.y / height;

  glBegin(GL_LINE_LOOP);
  glColor3f(1.f, 0.f, 0.f);
  glVertex3f(p1norm.x, p1norm.y, 0.0f);
  glVertex3f(p2norm.x, p1norm.y, 0.0f);
  glVertex3f(p2norm.x, p2norm.y, 0.0f);
  glVertex3f(p1norm.x, p2norm.y, 0.0f);
  glEnd();
}

void Hitbox::move(PointF const& p) {
  VectorF dv = { (rect.p2.x - rect.p1.x) / 2.0f, (rect.p2.y - rect.p1.y) / 2.0f };
  rect.p1 = p - dv;
  rect.p2 = p + dv;
}

void Hitbox::moveOn(VectorF const& direction) {
  rect.p1 += direction;
  rect.p2 += direction;
}

void Hitbox::resize(VectorF const& delta) {
  rect.p1 -= 0.5f * delta;
  rect.p2 += 0.5f * delta;
}

RectF Hitbox::getRect() const {
  return rect;
}

bool Hitbox::inBox(Hitbox const& other) const {
  return rect.p1.y >= other.rect.p1.y && rect.p1.x >= other.rect.p1.x &&
    rect.p2.y <= other.rect.p2.y && rect.p2.x <= other.rect.p2.x;
}

bool Hitbox::outBox(Hitbox const& other) const {
  return rect.p1.y >= other.rect.p2.y || rect.p1.x >= other.rect.p2.x ||
    rect.p2.y <= other.rect.p1.y || rect.p2.x <= other.rect.p1.x;
}

VectorF Hitbox::interspect(Hitbox const& other) const {
  float px = 0, py = 0;

  if (outBox(other) || inBox(other) || other.inBox(*this))
    return { 0, 0 };

  if (rect.p1.y < other.rect.p2.y && other.rect.p2.y < rect.p2.y) {
    float diff1 = other.rect.p2.y - rect.p1.y;
    float diff2 = rect.p2.y - other.rect.p2.y;

    py += diff1 > diff2 ? -diff2 : diff1;
  }

  if (rect.p1.y < other.rect.p1.y && other.rect.p1.y < rect.p2.y) {
    float diff1 = other.rect.p1.y - rect.p1.y;
    float diff2 = rect.p2.y - other.rect.p1.y;

    py += diff1 > diff2 ? -diff2 : diff1;
  }

  if (rect.p1.x < other.rect.p2.x && other.rect.p2.x < rect.p2.x) {
    float diff1 = other.rect.p2.x - rect.p1.x;
    float diff2 = rect.p2.x - other.rect.p2.x;

    px += diff1 > diff2 ? -diff2 : diff1;
  }

  if (rect.p1.x < other.rect.p1.x && other.rect.p1.x < rect.p2.x) {
    float diff1 = other.rect.p1.x - rect.p1.x;
    float diff2 = rect.p2.x - other.rect.p1.x;

    px += diff1 > diff2 ? -diff2 : diff1;
  }

  return { px, py };
}