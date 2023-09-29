#pragma once
#include "Points.h"
#include "../Graphics/Rendered.h"
#include "Hitbox.h"

class Colliding : public Rendered {
public:
  Colliding();
  Colliding(PointF const center, float width, float height);

  void moveTo(PointF const& p);
  void resize(VectorF const& delta);

  void draw(GLFWwindow* window) const override;
  virtual bool collided(Colliding const* other, VectorF& direction);
  virtual void moveOn(VectorF const& direction);

  bool out(Colliding const* other) const;
  bool in(Colliding const* other) const;

  RectF getRect() const;
  PointF center() const;
  float width() const;
  float height() const;

private:
  Hitbox m_box;
  PointF m_center;
  float m_width, m_height;
};