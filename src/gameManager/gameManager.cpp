#include <SFML/Graphics.hpp>
#include <SFML/Main.hpp>
#include "gameManager.h"

GameManager::GameManager() {
}

GameManager::~GameManager() {
}

void GameManager::init() {
  window.create(sf::VideoMode(800, 600), "My window");
  mainloop();
}

void GameManager::mainloop() {
  while (window.isOpen())
  {
    sf::Event event;
    while (window.pollEvent(event))
    {
      if (event.type == sf::Event::Closed)
      window.close();
    }

    window.clear();
    // Draw function here
    window.display();
  }
}
