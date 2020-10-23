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
void Raider::on_Notify(const Component* subject, Event event)
{

}

void Raider::_init()
{
    Entity::state = OUTER;
}

void Raider::_update()
{
    super::checkTargets();
}

void Raider::_draw(sf::RenderWindow & window)
{

}

double Raider::operator()()
{
    while (!Entity::isDead())
    {
        switch(state)
        {
            case OUTER:
            {
                break;
            }
            case EXPLORATION:
            {
                break;
            }
            case OFFENSIVE:
            {
                break;
            }
            case END_GAME:
            {
                break;
            }
            default:
            {
                Entity::state = EXPLORATION;
            }
        }
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
