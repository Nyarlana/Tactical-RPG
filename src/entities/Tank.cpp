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
void Tank::on_Notify(const Component* subject, Event event)
{

}

void Tank::_init()
{
    Entity::state = OUTER;
}

int Tank::stateValue()
{
    int value;

    switch (Entity::state)
    {
        case OUTER:
            value = 0;
            break;
        case SEARCH:
            value = 1;
            break;
        case PROTECTION:
            value = 2;
            break;
        case OFFENSIVE:
            value = 3;
            break;
        case END_GAME:
            value = 4;
            break;
        default:
            value = -1;
    }

    return value;
}

double Tank::operator()()
{
    while (!Entity::isDead())
    {
        switch(state)
        {
            case OUTER:
            {
                break;
            }
            case SEARCH:
            {
                break;
            }
            case PROTECTION:
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
                Entity::state = SEARCH;
            }
        }
    }

    return 0.0;
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
