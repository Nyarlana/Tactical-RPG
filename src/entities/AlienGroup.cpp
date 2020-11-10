#include "AlienGroup.h"

#include <memory>
#include <iostream>
#include <thread>

using namespace std;

AlienGroup::AlienGroup(int alien_number, int average_alien_stats) : alien_number(alien_number)
{
    for(int i=0; i<alien_number; i++)
    {
        std::shared_ptr<Alien> a = make_shared<Alien>(5, i, i, 3, 3, 5, true);
        aliens.push_back(a);
        //threads.push_back(thread(a*));
    }
}

//inherited functions
void AlienGroup::on_Notify(const Component* subject, Event event)
{
}

void AlienGroup::_init()
{
    for(int i=0; i<aliens.size(); i++)
        aliens[i]->_init();
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
    for(int i=0; i<threads.size(); i++)
        threads[i].join();
    std::cout << "This AlienGroup was eradicated" << '\n';
}
