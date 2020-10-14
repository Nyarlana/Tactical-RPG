#include "Tank.h"

#include <memory>
#include <vector>

using namespace std;

Tank::Tank(int xPos, int yPos) : Fighter(10, xPos, yPos, 2, 3, 4)
{
    //ctor
}

Tank::~Tank()
{
    //dtor
}

//inherited functions
void Tank::_init()
{

}

void Tank::_update()
{

}

void Tank::_draw(sf::RenderWindow & window)
{

}

void Tank::action()
{
    //dtor
}

void Tank::moveOut()
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
