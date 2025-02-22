#include "Tank.h"

#include "Alien.h"

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
void Tank::on_Notify(Component* subject, Event event)
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
        {
            value = 0;
            break;
        }
        case SEARCH:
        {
            value = 1;
            break;
        }
        case PROTECTION:
        {
            value = 2;
            break;
        }
        case OFFENSIVE:
        {
            value = 3;
            break;
        }
        case END_GAME:
        {
            value = 4;
            break;
        }
        default:
        {
            value = -1;
        }
    }

    return value;
}

std::string Tank::getStateS()
{
    std::string the_string;

    switch (Entity::state)
    {
        case OUTER:
            the_string = "OUTER"; break;
        case SEARCH:
            the_string = "SEARCH"; break;
        case PROTECTION:
            the_string = "PROTECTION"; break;
        case OFFENSIVE:
            the_string = "OFFENSIVE"; break;
        case END_GAME:
            the_string = "END_GAME"; break;
        default:
            the_string = "ERROR";
    }

    the_string += " : " + std::to_string(targets.size());
    return the_string;
}

void Tank::check()
{

}

void Tank::action()
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

void Tank::increaseThreat(shared_ptr<Entity> target, int threatIncrease)
{
    if(typeid(target.get())==typeid(Alien()))
        super::increaseThreat(target, threatIncrease);
}

void Tank::answer_radar(std::shared_ptr<Entity> e)
{
    if(!isDead())
    {
        shared_ptr<Entity> me = std::dynamic_pointer_cast<Entity>(Observer::shared_from_this());
        e->add(true,me);
    }
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

std::string Tank::tostring()
{
    return "tank";
}
