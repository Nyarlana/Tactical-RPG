#include <SFML/Graphics.hpp>
#include <SFML/Main.hpp>
#include <memory>
#include "gameManager/GameManager.h"

int main() {
  std::shared_ptr<GameManager> gm = std::make_shared<GameManager>();
  gm->init();
  return 0;
}
