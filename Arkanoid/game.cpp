#include "Game.h"
#include "GameSettings.h"

#include <algorithm>
#include <cstdlib>
#include <ctime>

Game::Game()
  : window(nullptr), height(0), width(0), room(nullptr), carriage(nullptr),
  board(nullptr), sticky(false), bottom(nullptr)
{}

Game::~Game() {
  for (auto& ball : balls)
    delete ball;

  for (auto& bonus : bonuses)
    delete bonus;

  for (auto& effect : effects)
    delete effect;

  delete bottom;
  delete carriage;
  delete room;
  delete board;
}

Game& Game::getInstance() {
  static Game game;
  return game;
}

void Game::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
  Game& game = Game::getInstance();
  
  int dir = game.carriage->GetDirection();
  switch (key)
  {
  case GLFW_KEY_A:
    if (action == GLFW_PRESS)
      dir = std::max({ -1, dir - 1 });
    else if (action == GLFW_RELEASE)
      dir = std::min({ 1, dir + 1 });
    break;
  case GLFW_KEY_D:
    if (action == GLFW_PRESS)
      dir = std::min({ 1, dir + 1 });
    else if(action == GLFW_RELEASE)
      dir = std::max({ -1, dir - 1 });
    break;
  case GLFW_KEY_SPACE:
    if (action != GLFW_RELEASE) {
      Ball* ball = game.carriage->spawnBall();
      if (ball) game.balls.push_back(ball);
    }
    break;
  }
  game.carriage->SetDirection(static_cast<Carriage::EDirections>(dir));
}

bool Game::initWindow() {
  glfwInit();
  glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

  window = glfwCreateWindow(GS::Win::width, GS::Win::height, "Arcanoid", nullptr, nullptr);
  if (window == nullptr)
    return false;

  glfwMakeContextCurrent(window);

  glfwGetFramebufferSize(window, &width, &height);
  glfwSetKeyCallback(window, Game::keyCallback);
  glViewport(0, 0, width, height);

  return true;
}

bool Game::initGameObjects() {
  srand(static_cast<unsigned int>(time(nullptr)));

  room = new Room(GS::GO::Room::center, GS::GO::Room::width, GS::GO::Room::height);
  
  carriage = new Carriage(GS::GO::Carriage::center, GS::GO::Carriage::baseWidth, 
    GS::GO::Carriage::height, GS::GO::Carriage::speed, GS::GO::Carriage::balls);

  board = new Board(GS::GO::Board::start, GS::GO::Board::width, GS::GO::Board::height,
    GS::GO::Bricks::width, GS::GO::Bricks::height, GS::GO::Board::brickMp, GS::GO::Board::bonusMp);

  return true;
}

bool Game::init() {
  if (!initWindow())
    return false;

  return initGameObjects();
}

void Game::update(float dt) {
  carriage->update(dt);
  board->update(dt);
  for (auto ball : balls)
    ball->update(dt);

  for (auto bonus : bonuses)
    bonus->update(dt);

  for (auto effect : effects)
    effect->update(dt);

  VectorF d;
  carriage->collided(room, d);
  board->collided(room, d);

  for (auto it1 = balls.begin(); it1 != balls.end();) {
    if (bottom && (*it1)->collided(bottom, d) && bottom->getDamage((*it1)) <= 0) {
      delete bottom;
      bottom = nullptr;
    }

    if ((*it1)->collided(room, d) && d.y > 0.0f) {
      delete* it1;
      it1 = balls.erase(it1);
      carriage->addBall();
      carriage->rewidth(GS::penalty);
      continue;
    };

    if (((*it1)->collided(carriage, d) && sticky) || (*it1)->out(room)) {
      delete* it1;
      it1 = balls.erase(it1);
      carriage->addBall();
      continue;
    }

    board->collided(*it1, this);
    
    auto it2 = it1;
    while (++it2 != balls.end()) {
      if ((*it1)->collided(*it2, d)) {
        (*it1)->moveOn(-1.5f * d);
        (*it2)->collided(*it1, d);
        (*it1)->moveOn(-0.5f * d);
      }
    }
    it1++;
  }

  for (auto it = bonuses.begin(); it != bonuses.end();) {
    if ((*it)->collided(carriage, d)) {
      effects.push_back((*it)->dropEffect());
      effects.back()->start(this);
      delete (*it);
      it = bonuses.erase(it);
    }
    else if ((*it)->collided(room, d) && d.y > 0.f) {
      (*it)->kill();
      delete (*it);
      it = bonuses.erase(it);
    }
    else it++;
  }

  for (auto it = effects.begin(); it != effects.end();) {
    if ((*it)->timeLeft() <= 0.f) {
      (*it)->end(this);
      delete (*it);
      it = effects.erase(it);
    }
    else it++;
  }
}

void Game::draw() {
  glClearColor(GS::Win::color3f[0], GS::Win::color3f[1], GS::Win::color3f[2], 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);

  room->draw(window);
  carriage->draw(window);
  board->draw(window);
  for (auto ball : balls)
    ball->draw(window);

  for (auto bonus : bonuses)
    bonus->draw(window);

  if (bottom) bottom->draw(window);

  glfwSwapBuffers(window);
}

int Game::run() {
  float start = static_cast<float>(glfwGetTime());
  while (!glfwWindowShouldClose(window))
  {
    glfwPollEvents();

    float end = static_cast<float>(glfwGetTime());
    float dt = end - start;
    start = end;
    update(dt);
    draw();
  }

  glfwTerminate();
  return 0;
}

void Game::pushBonus(Bonus* bonus) {
  bonuses.push_back(bonus);
}

void Game::rewidthCarriage(float delta) {
  carriage->rewidth(delta);
}

void Game::changeSticky() {
  sticky = !sticky;
}

void Game::accelerateBall(float accel) {
  for (auto ball : balls)
    ball->accelerate(accel);
}

void Game::addHealBottom(int heal) {
  if (!bottom && heal < 0)
    return;

  if (!bottom)
    bottom = new SaveBrick(GS::GO::Bricks::Save::center, GS::GO::Bricks::Save::width, 
      GS::GO::Bricks::Save::height, GS::GO::Bricks::Save::points);

  if (bottom->addHeal(heal) <= 0) {
    delete bottom;
    bottom = nullptr;
  }
}

void Game::addBall() {
  carriage->addBall();
}

void Game::deleteBall() {
  carriage->deleteBall();
}