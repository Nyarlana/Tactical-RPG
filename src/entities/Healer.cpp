#include "Healer.h"

#include <memory>
#include <vector>

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
void Healer::action()
{
    //dtor
}

void Healer::moveOut()
{
    //dtor
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

    if ( got == heal_targets.end() )
        heal_targets.emplace (heal_target, value);
    else
        heal_targets[got->first]+=value;
}

/** @brief heals the target's life points by ?? points
@param target target that will get a heal*/
void Healer::heal(std::shared_ptr<Entity> heal_target)
{
    heal_target->takeDamage(heal_power*-1);
}
