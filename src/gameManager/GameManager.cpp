/**@file game manager code*/
#include "GameManager.h"

#include <thread>
#include <iostream>

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

  pb = std::make_shared<UI_ProgressBar>(sf::Vector2i(48,48), sf::Vector2i(128, 16), 3, 100, 30);
  components.push_back(pb);
  pb->add_Observer(Observer::shared_from_this());

  ag = std::make_shared<AlienGroup>(2,5);
  ag->add_Observer(Observer::shared_from_this());
  components.push_back(ag);
  entities.push_back(std::thread(&AlienGroup::action, ag.get()));

  rb = std::make_shared<RoverBase>(RoverBase::launchMission("test"));
  rb->add_Observer(Observer::shared_from_this());
  components.push_back(rb);
  rb->notify(rb.get(), GM_ADD_THREAD);

  tb = std::make_shared<UI_TextBox>(sf::Vector2i(64,64), "Hello World");
  components.push_back(tb);
  tb->add_Observer(Observer::shared_from_this());

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
        {
          switch (event.key.code)
          {
            case sf::Keyboard::E:
            {
              testFunc();
              break;
            }
            case sf::Keyboard::P:
            {
              tm->printTab();
              break;
            }
            case sf::Keyboard::Left:
            {
              pb->substract_Value(5);
              break;
            }
            case sf::Keyboard::Right:
            {
              pb->add_Value(5);
              break;
            }
          }
          break;
        }
        case sf::Event::MouseButtonPressed :
        {
          if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
          {
            tb->set_Position(sf::Mouse::getPosition(window));
          }
        }
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
    case GM_ADD_THREAD:
    {
      entities.push_back(std::thread(ThreadContainer((Entity*) subject)));
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
