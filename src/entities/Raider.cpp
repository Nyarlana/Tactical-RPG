#include "Raider.h"

#include <memory>
#include <vector>

using namespace std;

Raider::Raider(int xPos, int yPos) : Fighter(6, xPos, yPos, 4, 3, 4)
{
    //ctor
}

Raider::~Raider()
{
    //dtor
}

//inherited functions
void Raider::_init()
{

}

void Raider::_update()
{

}

void Raider::_draw(sf::RenderWindow & window)
{

}

double Raider::operator()()
{
    while (lp>0)
    {
        //super::checkTargets();
    }

    return 0.0;
}

void Raider::attack(shared_ptr<Entity> target)
{
    target->takeDamage(5);
}

//Class skills
/** @brief raises the Raider's speed */
void Raider::speedup()
{
    speed++;
}

/** @brief decreases the Raider's threat value by ?? points the Aliens see in this Raider */
void Raider::lowProfile()
{
    //calls the GM to decrease this' threat for Aliens by ??
}
