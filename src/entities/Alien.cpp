#include "Alien.h"

#include <memory>
#include <vector>

using namespace std;

Alien::Alien() : Fighter(max_LP, xPos, yPos, speed, targetCheckArea, threatfulTargetCheckArea), hasAggressiveBehavior(hasAggressiveBehavior)
{
    //ctor
}

Alien::~Alien()
{
    //dtor
}

//inherited functions
void Alien::action()
{
    //dtor
}

void Alien::moveOut()
{
    //dtor
}

void Alien::die()
{
    //dtor
}

void Alien::attack(shared_ptr<Entity> target)
{
    target->takeDamage(2);
}
