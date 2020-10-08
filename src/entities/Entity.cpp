#include "Entity.h"

#include <memory>
#include <vector>
#include <iostream>

using namespace std;

Entity::Entity(int _max_LP, int _xPos, int _yPos, int _speed)
{
  max_LP = _max_LP;
  xPos = _xPos;
  yPos = _yPos;
  speed = _speed;
}

void Entity::takeDamage(int value) //critical section
{
    lp-=value;

    //notify taken damage

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
