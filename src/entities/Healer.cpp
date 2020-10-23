#include "Healer.h"

#include <memory>
#include <vector>
#include <list>

using namespace std;

Healer::Healer(int xPos, int yPos) : Fighter(8, xPos, yPos, 3, 1, 3)
{
    heal_power=2;
}

Healer::~Healer()
{
    //dtor
}

//inherited functions
void Healer::on_Notify(const Component* subject, Event event)
{

}

void Healer::_init()
{
    Entity::state = OUTER;
}

void Healer::_update()
{
    checkHealTargets();
    super::checkTargets();
}

void Healer::_draw(sf::RenderWindow & window)
{

}

double Healer::operator()()
{
    while (!Entity::isDead())
    {
        //state = choixTarget();

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
            case HEAL:
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

void Healer::attack(shared_ptr<Entity> target)
{
    target->takeDamage(1);
}

//Class skills
/** @brief changes heal need of a specific target, if the target isn't
already is the target list, adds it to the list
@param target target thats need of heal changes
@param value amount of point by which a target needs heal*/
void Healer::changeNeed(shared_ptr<Entity> heal_target, int value)
{
    unordered_map<shared_ptr<Entity>, int>::const_iterator got = heal_targets.find (heal_target);

    if ( got == heal_targets.end() && value > 0)
        heal_targets.emplace (heal_target, value);
    else
        heal_targets[got->first]+=value;

    //if(heal_targets[got->first]<1)
    //    heal_targets.erase[got->first];
}

/** @brief heals the target's life points by ?? points
@param target target that will get a heal*/
void Healer::heal(std::shared_ptr<Entity> heal_target)
{
    heal_target->takeDamage(heal_power*-1);
}

void Healer::checkHealTargets()
{
    list<shared_ptr<Entity>> to_remove;

    for ( auto it = heal_targets.cbegin(); it != heal_targets.cend(); ++it )
    {
        if(Entity::getDistanceTo(it->first)>Fighter::targetCheckArea)
            to_remove.push_back(it->first);
    }

    while(!to_remove.empty())
    {
        heal_targets.erase(to_remove.front());
        to_remove.pop_front();
    }
}
