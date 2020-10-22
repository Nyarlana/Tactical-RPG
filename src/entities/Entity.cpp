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

sf::Vector2i Entity::getPos()
{
    return pos;
}

int Entity::getDistanceTo(shared_ptr<Entity> e)
{
    int x = e.get()->getPos().x-pos.x;
    int y = e.get()->getPos().y-pos.y;

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

void Entity::moveTo(sf::Vector2i newPos)
{
    int x = newPos.x-pos.x;
    int y = newPos.y-pos.y;

    bool distanceOk = ((int) sqrt(x*x+y*y))==1;

    if(distanceOk)
    {
        pos = newPos;
    }
}

Entity::~Entity()
{
}
