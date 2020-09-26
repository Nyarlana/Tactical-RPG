/**@file game manager code*/
#include <SFML/Graphics.hpp>
#include <SFML/Main.hpp>
#include "gameManager.h"

GameManager::GameManager() {
}

GameManager::~GameManager() {
}

void GameManager::init() {
  window.create(sf::VideoMode(800, 600), "My window");
  window.setVerticalSyncEnabled(true);
  mainloop();
}

void GameManager::mainloop() {
  while (window.isOpen()) // game loop
  {
    // Event block : polls all SFML events, stock relevant ones in an array
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
