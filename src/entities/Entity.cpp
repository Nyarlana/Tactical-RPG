#include "Entity.h"

#include "../gameManager/Component.h"
#include <SFML/Graphics.hpp>

#include <memory>
#include <vector>
#include <iostream>

using namespace std;

Entity::Entity(int _max_LP, int _xPos, int _yPos, int _speed) : max_LP(_max_LP), lp(_max_LP), pos(sf::Vector2i(_xPos, _yPos)), speed(_speed)
{
}

int Entity::getXPos()
{
    return pos.x;
}

int Entity::getYPos()
{
    return pos.y;
}

int Entity::getDistanceTo(shared_ptr<Entity> e)
{
    int x,y;

    x = e.get()->getXPos()-pos.x;
    y = e.get()->getYPos()-pos.y;

    return (int) sqrt(x*x+y*y);
}

bool Entity::isDead()
{
    return lp<1;
}

void Entity::takeDamage(int value) //critical section
{
    lp-=value;

    //notify taken damage
    std::cout<<"An Entity took "<<value<<" damages\n";

    if(lp<=0)
    {
        die();
    }
    else if(lp>max_LP)
    {
        lp = max_LP;
    }
}

void Entity::die()
{
    std::cout<<"Deleted at "<<pos.x<<", "<<pos.y<<std::endl;
}

Entity::~Entity()
{
}
