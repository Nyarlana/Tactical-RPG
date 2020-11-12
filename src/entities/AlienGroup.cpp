#include "AlienGroup.h"

#include <memory>
#include <iostream>
#include <thread>

using namespace std;

AlienGroup::AlienGroup(int alien_number, int average_alien_stats) : alien_number(alien_number)
{
    for(int i=0; i<alien_number; i++)
    {
        std::shared_ptr<Alien> a = make_shared<Alien>(5, i+1, i+1, i+2, 3, 5, true);
        aliens.push_back(a);
    }
}

//inherited functions
void AlienGroup::on_Notify(Component* subject, Event event)
{
}

void AlienGroup::add_Observer(std::shared_ptr<Observer> obs)
{
    Subject::add_Observer(obs);

    for(int i=0; i<alien_number; i++)
    {
        aliens[i]->add_Observer(obs);
    }
}

void AlienGroup::_init()
{
    for(int i=0; i<aliens.size(); i++)
    {
        notify(aliens[i].get(), GM_ADD_THREAD);
        aliens[i]->_init();
    }
}

void AlienGroup::_update()
{
    for(int i=0; i<aliens.size(); i++)
        aliens[i]->_update();
}

void AlienGroup::_draw(sf::RenderWindow & window)
{
    for(int i=0; i<aliens.size(); i++)
        aliens[i]->_draw(window);
}

void AlienGroup::action()
{
}

void AlienGroup::die()
{
    std::cout << "This AlienGroup was eradicated" << '\n';
}
