/**@file game manager code*/
#include <SFML/Graphics.hpp>
#include <SFML/Main.hpp>
#include <memory>
#include <iostream>
#include "GameManager.h"
#include "Component.h"
#include "Observer.h"
#include "../TileMap/TileMap.h"

GameManager::GameManager() {
}

GameManager::~GameManager() {
}

void GameManager::init() {
  window.create(sf::VideoMode(800, 800), "Tactical Sim");
  window.setVerticalSyncEnabled(true);

  tm = std::make_shared<TileMap>();
  components.push_back(tm);
  tm->add_Observer(std::dynamic_pointer_cast<Observer>(shared_from_this()));

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
      if (components[i]->active) {
        components[i]->_update();
      }
    }

    window.clear();
    for (size_t i = 0; i < components.size(); i++) {
      if (components[i]->active) {
        components[i]->_draw(window);
      }
    }
    window.display();
  }
}

void GameManager::on_Notify(const Component& subject, Event event) {
  switch (event) {
    case EVENT_TEST:
      std::cout<<"Test event"<<std::endl;
  }
}
