#include "Tank.h"

#include <shared_ptr>
#include <vector>

using namespace std;

Tank::Tank() : Fighter(10, xPos, yPos, 2, 3, 4)
{
    //ctor
}

Tank::~Tank()
{
    //dtor
}

//inherited functions
void Tank::action()
{
    //dtor
}

void Tank::attack(shared_ptr<Entity> target)
{
    target->takeDamage(3);
}

//Class skills
/** @brief increases by ?? points the threat Aliens around see in this Tank */
void Tank::tease()
{
    //calls the GM to increase this' threat for Aliens by ??
}

/** @brief multiplies by ?? the threat the selected Alien see in this Tank */
void Tank::taunt(shared_ptr<Alien> alien)
{
    //alien->increaseThreat(shared_ptr<Entity>(this), ??)
}
