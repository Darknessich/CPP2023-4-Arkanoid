#include "Board.h"
#include "AccelBrick.h"
#include "IndestructibleBrick.h"
#include "MovingBrick.h"
#include "../../GameSettings.h"
#include "../Bonus/Bonus.h"
#include "../Bonus/IncreaseSize.h"
#include "../Bonus/Downsizing.h"
#include "../Bonus/Accelerate.h"
#include "../Bonus/Slowdown.h"
#include "../Bonus/SaveBonus.h"
#include "../Bonus/StickyCarriage.h"
#include "../Bonus/AddBall.h"
#include "../../game.h"

Bonus* getBonus(char name) {
  switch (name) {
  case 'n': // none
    return nullptr;
  case 'i': // increase
    return new Bonus(new IncreaseSize());
  case 'd': // downsizing
    return new Bonus(new Downsizing());
  case 't': // sticky
    return new Bonus(new StickyCarriage());
  case 'a': // accelerate
    return new Bonus(new Accelerate());
  case 'l': // slowdown
    return new Bonus(new Slowdown());
  case 's': // save
    return new Bonus(new SaveBonus());
  case 'b': // addball
    return new Bonus(new AddBall());

  }
  return nullptr;
}

Board::Board(PointF start, int wb, int hb, float brickW, float brickH, char const* const bricksMap[], char const* const bonusMap[])
  : Moving({ start.x + wb * brickW / 2.0f, start.y + hb * brickH / 2.0f }, wb* brickW, hb* brickH),
  start({ start.x + brickW / 2.0f, start.y + brickH / 2.0f }),
  wb(wb), hb(hb), brickW(brickW), brickH(brickH)
{
  for (int i = 0; i < hb; i++) {
    PointF line(this->start.x, this->start.y - i * brickH);
    for (int j = 0; j < wb; j++) {
      switch (bricksMap[i][j]) {
      case 'n': // None
        break;
      case 'b': // Brick
        bricks.push_back(new Brick(line + PointF(j * brickW, 0.0f), brickW, brickH, GS::GO::Bricks::Brick::points, getBonus(bonusMap[i][j])));
        break;
      case 'a': // AccelBrick
        bricks.push_back(new AccelBrick(line + PointF(j * brickW, 0.0f), brickW, brickH, GS::GO::Bricks::Accel::points, getBonus(bonusMap[i][j]), GS::GO::Bricks::Accel::accel));
        break;
      case 'i': // IndestructibleBrick
        bricks.push_back(new IndestructibleBrick(line + PointF(j * brickW, 0.0f), brickW, brickH, GS::GO::Bricks::Indestruct::points, getBonus(bonusMap[i][j])));
        break;
      case 'm': // MovingBrick
        movBricks.push_back(new MovingBrick(line + PointF(j * brickW, 0.0f), brickW, brickH, GS::GO::Bricks::Moving::points, getBonus(bonusMap[i][j]), { GS::GO::Bricks::Moving::speed, 0.0f }));
        break;
      }
    }
  }
}

Board::~Board() {
  for (auto& brick : bricks)
    delete brick;

  for (auto& mbrick : movBricks)
    delete mbrick;
}

void Board::draw(GLFWwindow* window) const {
  for (auto brick : bricks)
    brick->draw(window);

  for (auto mbrick : movBricks)
    mbrick->draw(window);

  Colliding::draw(window);
}

bool Board::collided(Colliding const* other, VectorF& direction) {
  bool iscollided = false;
  for (auto brick : bricks)
    iscollided = iscollided || brick->collided(other, direction);

  for (auto mbrick : movBricks)
    iscollided = iscollided || mbrick->collided(other, direction);

  return iscollided;
}

void Board::update(float dt) {
  for (auto mbrick : movBricks)
    mbrick->update(dt);
  
  VectorF dir;
  for (auto it1 = movBricks.begin(); it1 != movBricks.end(); it1++) {
    for (auto brick : bricks)
      (*it1)->collided(brick, dir);

    auto it2 = it1;
    while (++it2 != movBricks.end()) {
      (*it1)->collided(*it2, dir);
      (*it1)->moveOn(-0.5f * dir);
      (*it2)->collided(*it1, dir);
    }
  }
}

void Board::collided(Ball* ball, Game* game) {
  VectorF dir;
  Bonus* bonus;
  for (auto it = bricks.begin(); it != bricks.end();)
    if (ball->collided(*it, dir) && (*it)->getDamage(ball) == 0) {
      if (bonus = (*it)->dropBonus()) game->pushBonus(bonus);
      delete (*it);
      it = bricks.erase(it);
    } else it++;

  for (auto it = movBricks.begin(); it != movBricks.end();)
    if (ball->collided(*it, dir) && (*it)->getDamage(ball) == 0) {
      if (bonus = (*it)->dropBonus()) game->pushBonus(bonus);
      delete (*it);
      it = movBricks.erase(it);
    } else it++;
}