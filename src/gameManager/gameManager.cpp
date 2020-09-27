/**@file game manager code*/
#include <SFML/Graphics.hpp>
#include <SFML/Main.hpp>
#include <memory>
#include "gameManager.h"
#include "component.h"

GameManager::GameManager() {
}

GameManager::~GameManager() {
}

void GameManager::init() {
  window.create(sf::VideoMode(800, 600), "My window");
  window.setVerticalSyncEnabled(true);

  for (size_t i = 0; i < components.size(); i++) {
    components[i]->_init();
  }

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

    for (size_t i = 0; i < components.size(); i++) {
      components[i]->_update();
    }

    window.clear();
    for (size_t i = 0; i < components.size(); i++) {
      components[i]->_draw();
    }
    window.display();
  }
}
