#include "Entity.h"

#include "../gameManager/Component.h"

#include <memory>
#include <vector>
#include <iostream>

using namespace std;

Entity::Entity(int _max_LP, int _xPos, int _yPos, int _speed) : max_LP(_max_LP), lp(_max_LP), xPos(_xPos), yPos(_yPos), speed(_speed)
{
}

int Entity::getXPos()
{
    return xPos;
}

int Entity::getYPos()
{
    return yPos;
}

int Entity::getDistanceTo(shared_ptr<Entity> e)
{
    int x,y;

    x = e.get()->getXPos()-xPos;
    y = e.get()->getYPos()-yPos;

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
    std::cout<<"Deleted at "<<xPos<<", "<<yPos<<std::endl;
}

Entity::~Entity()
{
}
