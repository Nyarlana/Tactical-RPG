/**@file game manager code*/
#include <SFML/Graphics.hpp>
#include <SFML/Main.hpp>
#include <thread>
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
  tm->add_Observer(Observer::shared_from_this());

  pb = std::make_shared<UI_ProgressBar>(sf::Vector2i(48,48), sf::Vector2i(128, 16), 100, 30);
  components.push_back(pb);
  pb->add_Observer(Observer::shared_from_this());

  v_a.push_back(std::make_shared<Alien>());
  v_a.push_back(std::make_shared<Alien>(5, 5, 5, 4, 3, 5, true));


  for(int i=0; i<v_a.size(); i++)
  {
      v_a[i]->add_Observer(Observer::shared_from_this());
      components.push_back(v_a[i]);
      entities.push_back(std::thread(*v_a[i]));
  }


  for (size_t i = 0; i < components.size(); i++)
  {
    components[i]->_init();
  }

  mainloop();

  // for (size_t i = 0; i < entities.size(); i++)
  // {
  //   entities[i].detach();
  // }
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
              break;
            case sf::Keyboard::A:
              v_a.push_back(std::make_shared<Alien>(12,12));
              v_a.back()->add_Observer(Observer::shared_from_this());
              components.push_back(v_a.back());
              entities.push_back(std::thread(*v_a.back()));
              components.back()->_init();
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

void GameManager::on_Notify(Component* subject, Event event)
{
  switch (event)
  {
    case EVENT_TEST:
    {
      std::cout<<"Test event"<<std::endl;
      break;
    }
    case E_GET_RANDOM_PATH:
    {
      Entity* e = (Entity*) subject;
      e->setPath(tm->getRandomMove(e->getPos()));
      break;
    }
    case GM_ADD_COMPONENT:
    {
      std::shared_ptr<Component> temp;
      temp.reset(subject);
      add_Component(temp);
      break;
    }
  }
}

void GameManager::add_Component(const std::shared_ptr<Component> comp) {
  components.push_back(comp);
  comp->_init();
}

void GameManager::testFunc()
{
  tm->testFunc();
}
