/**@file game manager code*/
#include "GameManager.h"

#include "Parameters.h"

#include <iostream>

// sf::Clock GameManager::clock = new sf::Clock;

GameManager::GameManager() : m(new std::mutex())
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


  for (size_t i = 0; i < ag.size(); i++)
  {
      ag[i]->add_Observer(Observer::shared_from_this());
      ag[i]->add_Observer(tm->shared_from_this());
      components.push_back(ag[i]);
      entities.push_back(std::thread(&AlienGroup::action, ag[i].get()));
  }

  rb->add_Observer_and_Rovers(Observer::shared_from_this());
  // rb->add_Observer_and_Rovers(tm->shared_from_this());
  // rb->add_Observer_and_Rovers(rb->shared_from_this());
  std::cout << "heeeeeeiiiiiiinnnnnnn ?????" << '\n';
  rb->notify(rb.get(), GM_ADD_THREAD);
  std::cout << "sop cétrolol" << '\n';
  components.push_back(rb);

  tb = std::make_shared<UI_TextBox>(sf::Vector2i(64,64), "Hello World");
  components.push_back(tb);
  tb->add_Observer(Observer::shared_from_this());

  for (size_t i = 0; i < components.size(); i++)
  {
    components[i]->_init();
  }

  mainloop();
}

void GameManager::mainloop()
{
  bool once = true;
  while (window.isOpen()) // game loop
  {
    window.setTitle("Tactical Sim - " + std::to_string(rb->getOreAmount()) + "/" + std::to_string(rb->getObjective()));
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
            vp = std::make_shared<UI_VisualPath>(tm->request_path(sf::Vector2i(3,3), sf::Vector2i(X_SIZE-2,4)));
            start = std::make_shared<UI_Point>(sf::Vector2i(3,3));
            finish = std::make_shared<UI_Point>(sf::Vector2i(X_SIZE-2,4), sf::Color::Blue);
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
      if (components[i]->is_Active())
      {
         components[i]->_update();
      }
    }

    window.clear();
    for (size_t i = 0; i < components.size(); i++)
    {
      if (components[i]->is_Active())
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
    case E_GET_RANDOM_POS:
    {
      m->lock();
      AlienGroup* a = (AlienGroup*) subject;
      a->setPos(tm->getRandomValidPosition());
      m->unlock();
      break;
    }
    case E_GET_RANDOM_PATH:
    {
      m->lock();
      Entity* e = (Entity*) subject;
      e->setPath(tm->getRandomMove(e->getPos()));
      m->unlock();
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
      std::cout << "oh un thread " << ((Entity*) subject)->getID() << '\n';
      m->lock();
      entities.push_back(std::thread(ThreadContainer((Entity*) subject)));
      m->unlock();
      break;
    }
    case E_EXP_ORE_CHECK:
    {
        m->lock();
        Miner* e = (Miner*) subject;
        std::vector<sf::Vector2i> pos = tm->lookForOre(e->getPos(), 2);

        for(int i=0; i<pos.size(); i++)
            e->addOreObjective(pos[i]);

        m->unlock();
        break;
    }
    case E_GET_PATH_E_TARGET:
    {
        m->lock();
        Fighter* e = (Fighter*) subject;

        if(TRACE_EXEC)
            std::cout << "je cherche à atteindre ma cible" << '\n';

        sf::Vector2i t_pos = e->getTopTarget()->getPos();

        compute_and_set_path(e, t_pos);
        m->unlock();

        break;
    }
    case E_GET_PATH_ORE:
    {
        m->lock();
        Miner* e = (Miner*) subject;

        if(TRACE_EXEC)
            std::cout << "acquiring miner position..." << '\n';
        sf::Vector2i m_start_pos = e->getPos();

        if(TRACE_EXEC)
            std::cout << m_start_pos.x<<","<<m_start_pos.y<<"\n\nacquiring miner's top target position..." << '\n';
        sf::Vector2i o_pos = e->getTopOre();

        compute_and_set_path(e, o_pos);
        m->unlock();

        break;
    }
    case E_MINE_OCCURS:
    {
        m->lock();
        Miner* e = (Miner*) subject;

        if(TRACE_EXEC)
            std::cout << "mining ore..." << '\n';
        if(tm->mine(e->getTopOre()))
        {
            e->fillBag();
            std::cout << "bag was filled" << '\n';
        }
        m->unlock();
        break;
    }
    case E_MOVE:
    {
        m->lock();
        Entity* e = (Entity*) subject;
        if(tm->check_and_move(e->getPos(), e->getNextPos()))
            e->setPos(e->getNextPos());
        m->unlock();
        break;
    }
    case E_REQ_PATH_BASE:
    {
        m->lock();
        Entity* e = (Entity*) subject;

        if(TRACE_EXEC)
        {
            std::cout << "acquiring entity position..." << e->getPos().x<<","<<e->getPos().y<< '\n';
            std::cout <<"\n\nacquiring base position..." << '\n';
        }

        sf::Vector2i b_pos = rb->getPos();

        compute_and_set_path(e, b_pos);
        m->unlock();

        break;
    }
    case E_LF_ROV:
    {
        m->lock();
        rb->answer_radar(
            std::dynamic_pointer_cast<Entity>(
                ((Entity*) subject)->shared_from_this()
            )
        );
        m->unlock();
        break;
    }
    case E_LF_AL:
    {
        m->lock();
        for(int i =0; i<ag.size(); i++)
            ag[i]->answer_radar(
                std::dynamic_pointer_cast<Entity>(
                    ((Entity*) subject)->shared_from_this()
                )
            );
        m->unlock();
        break;
    }
    case E_OUT_REQ:
    {
        m->lock();
        Entity* e = (Entity*) subject;
        e->setPos(tm->getRandomMove(rb->getPos()).back());
        m->unlock();
        break;
    }
    case E_DEP_ORE:
    {
        m->lock();
        rb->getOneOre();

        if(TRACE_EXEC)
            std::cout << "ore deposited" << '\n';
        m->unlock();
        break;
    }
    case THIS_IS_A_WIN:
    {
        for(int i=0; i<entities.size(); i++)
            entities[i].detach();

        if(TRACE_EXEC)
            std::cout << "Rovers got enough ore !" << '\n';

        window.close();
    }
    case THIS_IS_A_LOOSE:
    {
        for(int i=0; i<entities.size(); i++)
            entities[i].detach();

        if(TRACE_EXEC)
            std::cout << "Aliens succeeded in keeping their ore !" << '\n';

        window.close();
    }
    case E_DIED:
    {
        std::shared_ptr<Entity> test1 = std::dynamic_pointer_cast<Entity>(
                std::dynamic_pointer_cast<RoverBase>(
            ((RoverBase*) subject)->shared_from_this()
        ));

        if(test1!=nullptr)
            test1->die();
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

void GameManager::setRoverBase(std::string mission)
{
    rb = std::make_shared<RoverBase>(RoverBase::launchMission(mission));
}

void GameManager::addAlienGroup(int alien_number, int alien_average_stats)
{
    ag.push_back(std::make_shared<AlienGroup>(alien_number, alien_average_stats));
}

void GameManager::compute_and_set_path(Entity* e, sf::Vector2i e_target)
{
    sf::Vector2i e_start = e->getPos();

    if(true)//if distance with ore >=2 then compute path with request_path
    {
        if(TRACE_EXEC)
            std::cout << e_target.x<<","<<e_target.y<<"\n\ncomputing path to the acquired position..." << '\n';
        std::vector<sf::Vector2i> path = tm->request_path(e_start,e_target);

        if(TRACE_EXEC)
            std::cout << "path length : "<<path.size()<<"\n\nsending path to the entity" << '\n';
        e->setPath(path);
    }
    else
        e->setPos(tm->getRandomMove(e_target).back());
}
