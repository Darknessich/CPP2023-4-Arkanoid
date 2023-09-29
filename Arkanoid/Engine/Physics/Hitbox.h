#pragma once
#include "../Graphics/Rendered.h"
#include "Points.h"

class Hitbox : public Rendered {
public:
  Hitbox(PointF const& p1, PointF const& p2);

  void draw(GLFWwindow* window) const override;

  void move(PointF const& p);
  void moveOn(VectorF const& direction);
  void resize(VectorF const& delta);
  RectF getRect() const;

  bool inBox(Hitbox const& other) const;
  bool outBox(Hitbox const& other) const;
  VectorF interspect(Hitbox const& other) const;
protected:
  RectF rect;
};