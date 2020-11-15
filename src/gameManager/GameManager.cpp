/**@file game manager code*/
#include "GameManager.h"

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

  ag = std::make_shared<AlienGroup>(3,5);
  ag->add_Observer(Observer::shared_from_this());
  components.push_back(ag);
  entities.push_back(std::thread(&AlienGroup::action, ag.get()));

  rb = std::make_shared<RoverBase>(RoverBase::launchMission("test"));
  rb->add_Observer_and_Rovers(Observer::shared_from_this());
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
  bool once = true;
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
          else if (sf::Mouse::isButtonPressed(sf::Mouse::Right) && once)
          {
            vp = std::make_shared<UI_VisualPath>(tm->request_path(sf::Vector2i(3,3), sf::Vector2i(23,5)));
            start = std::make_shared<UI_Point>(sf::Vector2i(3,3));
            finish = std::make_shared<UI_Point>(sf::Vector2i(23,5), sf::Color::Blue);
            components.push_back(vp);
            components.push_back(start);
            components.push_back(finish);
            once = false;
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
    case E_EXP_ORE_CHECK:
    {
        Miner* e = (Miner*) subject;
        std::vector<sf::Vector2i> pos = tm->lookForOre(e->getPos(), 2);

        for(int i=0; i<pos.size(); i++)
            e->addOreObjective(pos[i]);

        break;
    }
    case E_GET_PATH_E_TARGET:
    {
        Fighter* e = (Fighter*) subject;

        sf::Vector2i t_pos = e->getTopTarget()->getPos();

        compute_and_set_path(e, t_pos);

        break;
    }
    case E_GET_PATH_ORE:
    {
        Miner* e = (Miner*) subject;

        std::cout << "acquiring miner position..." << '\n';
        sf::Vector2i m_start_pos = e->getPos();

        std::cout << m_start_pos.x<<","<<m_start_pos.y<<"\n\nacquiring miner's top target position..." << '\n';
        sf::Vector2i o_pos = e->getTopOre();

        compute_and_set_path(e, o_pos);

        break;
    }
    case E_MINE_OCCURS:
    {
        Miner* e = (Miner*) subject;
        std::cout << "mining ore..." << '\n';
        tm->mine(e->getTopOre());
        break;
    }
    case E_REQ_PATH_BASE:
    {
        Entity* e = (Entity*) subject;

        std::cout << "acquiring entity position..." << e->getPos().x<<","<<e->getPos().y<< '\n';

        std::cout <<"\n\nacquiring base position..." << '\n';
        sf::Vector2i b_pos = rb->getPos();

        compute_and_set_path(e, b_pos);

        break;
    }
    case E_LF_ROV:
    {
        rb->answer_radar(
            std::dynamic_pointer_cast<Entity>(
                ((Entity*) subject)->shared_from_this()
            )
        );
        break;
    }
    case E_LF_AL:
    {
        ag->answer_radar(
            std::dynamic_pointer_cast<Entity>(
                ((Entity*) subject)->shared_from_this()
            )
        );
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

void GameManager::compute_and_set_path(Entity* e, sf::Vector2i e_target)
{
    sf::Vector2i e_start = e->getPos();

    if(false)//if distance with ore >=2 then compute path with request_path
    {
        std::cout << e_target.x<<","<<e_target.y<<"\n\nacquiring a position around entity's target..." << '\n';
        sf::Vector2i m_end_pos = tm->getRandomMove(e_target).back();

        std::cout << m_end_pos.x<<","<<m_end_pos.y<<"\n\ncomputing path to the acquired position..." << '\n';
        std::vector<sf::Vector2i> path = tm->request_path(e_start,m_end_pos);

        std::cout << "path length : "<<path.size()<<"\n\nsending path to the entity" << '\n';
        e->setPath(path);
    }
    else
        e->setPos(tm->getRandomMove(e_target).back());
}
