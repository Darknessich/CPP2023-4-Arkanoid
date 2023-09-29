#pragma once
#include <list>
#include <GLFW/glfw3.h>

#include "GameObjects/Ball.h"
#include "GameObjects/Room.h"
#include "GameObjects/Carriage.h"
#include "GameObjects/Bonus/Bonus.h"
#include "GameObjects/Bonus/Effect.h"
#include "GameObjects/Bricks/Board.h"
#include "GameObjects/Bricks/SaveBrick.h"

class Game {
  typedef std::list<Ball*> Balls;
  typedef std::list<Bonus*> Bonuses;
  typedef std::list<Effect*> Effects;

  Game();

  static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

  bool initWindow();
  bool initGameObjects();

  void update(float dt);
  void draw();
public:
  Game(Game const &) = delete;
  Game& operator=(Game const&) = delete;
  Game(Game&&) = delete;
  Game& operator=(Game&&) = delete;
  ~Game();

  static Game& getInstance();

  void pushBonus(Bonus* bonus);
  void rewidthCarriage(float width);
  void changeSticky();
  void accelerateBall(float accel);
  void addHealBottom(int heal);
  void addBall();
  void deleteBall();

  bool init();
  int run();
private:
  GLFWwindow* window;
  int width, height;
  bool sticky;

  Room* room;
  Carriage* carriage;
  Board* board;
  SaveBrick* bottom;

  Balls balls;
  Bonuses bonuses;
  Effects effects;
};