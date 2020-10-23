#include "Alien.h"

#include <memory>
#include <vector>
#include <iostream>

using namespace std;

Alien::Alien(int max_LP, int xPos, int yPos, int speed, int targetCheckArea, int threatfulTargetCheckArea, bool hasAggressiveBehavior) : Fighter(max_LP, xPos, yPos, speed, targetCheckArea, threatfulTargetCheckArea), hasAggressiveBehavior(hasAggressiveBehavior)
{
    //ctor
}

//inherited functions
void Alien::_init()
{
    Entity::state = SEARCH;
}

void Alien::_update()
{

}

void Alien::_draw(sf::RenderWindow & window)
{

}

double Alien::operator()()
{
    while (!Entity::isDead())
    {
        super::checkTargets();

        switch(state)
        {
            case SEARCH:
            {
                break;
            }
            case OFFENSIVE:
            {
                break;
            }
            default:
            {
                Entity::state = SEARCH;
            }
        }
    }

    return 0.0;
}

void Alien::die()
{
    //dtor
}

void Alien::attack(shared_ptr<Entity> target)
{
    target->takeDamage(2);

    if (target->isDead())
    {
        targets.erase(target);
    }
}
