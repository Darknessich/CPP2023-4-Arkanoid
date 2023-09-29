#include "Points.h"

PointF::PointF() {}

PointF::PointF(float x, float y)
  :x(x), y(y)
{}

PointF& PointF::operator+=(PointF const& p) {
  this->x += p.x;
  this->y += p.y;
  return *this;
}

PointF& PointF::operator-=(PointF const& p) {
  this->x -= p.x;
  this->y -= p.y;
  return *this;
}

PointF& PointF::operator*=(float a) {
  this->x *= a;
  this->y *= a;
  return *this;
}

PointF operator+(PointF pl, PointF const& pr) {
  return pl += pr;
}

PointF operator-(PointF pl, PointF const& pr) {
  return pl -= pr;
}

PointF operator*(float a, PointF p) {
  return p *= a;
}

PointF operator*(PointF p, float a) {
  return p *= a;
}