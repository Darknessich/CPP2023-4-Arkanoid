#include "game.h"

int main() {
  Game& game = Game::getInstance();
  game.init();
  return game.run();
}