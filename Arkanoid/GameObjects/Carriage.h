#pragma once
#include "Moving.h"
#include "Ball.h"

class Carriage : public Moving {
public:
  enum EDirections {
    D_LEFT = -1,
    D_NONE = 0,
    D_RIGHT = 1
  };

  Carriage(PointF center, float width, float height, float maxSpeed, int balls);
  
  void draw(GLFWwindow* window) const override;
  bool collided(Colliding const* other, VectorF& direction) override;
  void moveOn(VectorF const& direction) override;
  void update(float dt) override;
  
  void SetDirection(EDirections dir);
  EDirections GetDirection() const;

  void addBall();
  void deleteBall();
  Ball* spawnBall();
  void rewidth(float delta);
private:
  EDirections direction;
  float speed, maxSpeed;
  int balls;
};