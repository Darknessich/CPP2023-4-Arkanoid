#pragma once

typedef struct PointF {
  float x = 0.0f, y = 0.0f;
  PointF();
  PointF(float x, float y);
  PointF& operator+=(PointF const& p);
  PointF& operator-=(PointF const& p);
  PointF& operator*=(float a);
} VectorF;

PointF operator+(PointF pl, PointF const& pr);
PointF operator-(PointF pl, PointF const& pr);
PointF operator*(float a, PointF p);
PointF operator*(PointF p, float a);

struct RectF {
  PointF p1, p2;
};