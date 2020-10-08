#include "Entity.h"

#include <shared_ptr>
#include <vector>

using namespace std;

Entity::Entity() : max_LP(max_LP), xPos(xPos), yPos(yPos), speed(speed)
{
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
