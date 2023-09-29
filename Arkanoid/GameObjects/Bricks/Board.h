#pragma once

#include <list>

#include "Brick.h"
#include "../Moving.h"
#include "MovingBrick.h"
class Game;

class Board : Moving {
  typedef std::list<Brick*> Bricks;
  typedef std::list<MovingBrick*> MovBricks;

public:
  Board(PointF start, int wb, int hb, float brickW, float brickH, char const* const bricksMap[], char const* const bonusMap[]);
  ~Board();

  void draw(GLFWwindow* window) const override;
  bool collided(Colliding const* other, VectorF& direction) override;
  void update(float dt) override;

  void collided(Ball* ball, Game* game);
private:
  Bricks bricks;
  MovBricks movBricks;

  PointF start;
  int wb, hb;
  float brickW, brickH;
};