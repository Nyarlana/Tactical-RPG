#include "Alien.h"

#include <SFML/Graphics.hpp>

#include "Healer.h"
#include "Raider.h"
#include "Tank.h"
//#include "Rover.h"

#include <memory>
#include <vector>
#include <iostream>

using namespace std;

Alien::Alien(int max_LP, int xPos, int yPos, int speed, int targetCheckArea, int threatfulTargetCheckArea, bool hasAggressiveBehavior) : Fighter(max_LP, xPos, yPos, speed, targetCheckArea, threatfulTargetCheckArea), hasAggressiveBehavior(hasAggressiveBehavior)
{
    //ctor
}

//inherited functions
void Alien::on_Notify(const Component* subject, Event event)
{

}

void Alien::_init()
{
    std::cout << "alien _init start" << std::endl;
    Entity::state = SEARCH;
    std::cout << "alien state set" << std::endl;

    if(!texture.loadFromFile("data/entities/alien.png"))
    {
      if(!texture.loadFromFile("../data/entities/alien.png"))
      {
        std::cout << "erreur" << '\n';
      }
    }
    std::cout << "alien texture searched" << std::endl;

    sprite.setTexture(texture);
    std::cout << "alien texture set" << std::endl;
    sprite.setTextureRect(sf::IntRect(0,0,32,32));

    std::cout << "alien _init end" << std::endl;
}

int Alien::stateValue()
{
    int value;

    switch (Entity::state)
    {
        case SEARCH:
            value = 0;
            break;
        case OFFENSIVE:
            value = 1;
            break;
        default:
            value = -1;
    }

    return value;
}

void Alien::action()
{
    pause();

    if(targets.empty())
        state = SEARCH;
    else //if(hasAggressiveBehavior || )
        state = OFFENSIVE;

    switch(state)
    {
        case SEARCH:
        {
            if(path.empty())
                notify(this, E_GET_RANDOM_PATH);
            moveTo(path.back());
            path.pop_back();
            break;
        }
        case OFFENSIVE:
        {
            shared_ptr<Entity> t = getTopTarget();

            if(target_distance<2)
            {
                attack(t);
            }
            else
            {
                if(target_distance < getDistanceTo(t))
                    notify(this, E_GET_PATH_TARGET);

                moveTo(path.back());
                path.pop_back();

                target_distance = getDistanceTo(t);
            }
            break;
        }
        default:
        {
            Entity::state = SEARCH;
        }
    }
}

void Alien::die()
{
    std::cout << "An alien just died at (" << Entity::pos.x << "," << Entity::pos.y << ")" << '\n';
}

void Alien::increaseThreat(shared_ptr<Entity> target, int threatIncrease)
{
    if(typeid(target.get())!=typeid(Alien()))
    {
        super::increaseThreat(target, threatIncrease);

        if(targets.empty())
            Entity::state = SEARCH;
        else
            Entity::state = OFFENSIVE;
    }
}

void Alien::attack(shared_ptr<Entity> target)
{
    if(typeid(target.get())!=typeid(Alien()))
    {
        target->takeDamage(2);

        if (target->isDead())
        {
            targets.erase(target);
        }
    }
}
