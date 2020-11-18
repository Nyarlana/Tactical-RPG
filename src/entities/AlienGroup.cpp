#include "AlienGroup.h"

#include <memory>
#include <iostream>
#include <thread>

using namespace std;

AlienGroup::AlienGroup(int alien_number, int average_alien_stats) : alien_number(alien_number), group_number(++alienGroupNumber)
{
    std::cout << "AlienGroup n°" << group_number << '\n';

    for(int i=0; i<alien_number; i++)
    {
        aliens.push_back(make_shared<Alien>(5, 4*group_number+i+3, i+3, i*2+2, group_number, 3, 5));
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
        // aliens[i]->add_Observer(Observer::shared_from_this());
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

void AlienGroup::answer_radar(std::shared_ptr<Entity> e)
{
    for(int i=0; i<alien_number; i++)
    {
        aliens[i]->answer_radar(e);
    }
}

int AlienGroup::getGroup()
{
    return group_number;
}
