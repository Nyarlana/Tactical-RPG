/**@file game manager code*/
#include <SFML/Graphics.hpp>
#include <SFML/Main.hpp>
#include <memory>
#include <iostream>
#include "GameManager.h"
#include "Component.h"
#include "Observer.h"
#include "../TileMap/TileMap.h"

// sf::Clock GameManager::clock = new sf::Clock;

GameManager::GameManager()
{
}

GameManager::~GameManager()
{
}

void GameManager::init()
{
  window.create(sf::VideoMode(800, 800), "Tactical Sim");
  window.setVerticalSyncEnabled(true);

  tm = std::make_shared<TileMap>();
  components.push_back(tm);
  tm->add_Observer(shared_from_this());

  pb = std::make_shared<UI_ProgressBar>(sf::Vector2i(48,48), sf::Vector2i(128, 16), 100, 30);
  components.push_back(pb);
  pb->add_Observer(shared_from_this());

  for (size_t i = 0; i < components.size(); i++)
  {
    components[i]->_init();
  }

  // testFunc();

  mainloop();
}

void GameManager::mainloop()
{
  while (window.isOpen()) // game loop
  {
    // Event block : polls all SFML events, stock relevant ones in an array
    sf::Event event;
    while (window.pollEvent(event))
    {
      switch (event.type) {
        case sf::Event::Closed:
          window.close();
          break;
        case sf::Event::KeyPressed :
          switch (event.key.code) {
            case sf::Keyboard::E:
              testFunc();
              break;
            case sf::Keyboard::P:
              tm->printTab();
              break;
            case sf::Keyboard::Left:
              pb->substract_Value(5);
              break;
            case sf::Keyboard::Right:
              pb->add_Value(5);
          }
          break;
      }
    }

    for (size_t i = 0; i < components.size(); i++)
    {
      if (components[i]->active)
      {
        components[i]->_update();
      }
    }

    window.clear();
    for (size_t i = 0; i < components.size(); i++)
    {
      if (components[i]->active)
      {
        components[i]->_draw(window);
      }
    }
    window.display();
  }
}

void GameManager::on_Notify(const Component* subject, Event event)
{
  switch (event)
  {
    case EVENT_TEST:
      std::cout<<"Test event"<<std::endl;
  }
}

void GameManager::testFunc()
{
  tm->testFunc();
}
