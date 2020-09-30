#include "Entity.h"

Entity::Entity(int max_LP, int xPos, int yPos, int speed)
{
    this.max_LP = max_LP;
    this.lp     = max_LP;
    this.xPos   = xPos;
    this.yPos   = yPos;
    this.speed  = speed;
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
    ~Entity();
}

Entity::~Entity()
{
    //dtor
}
