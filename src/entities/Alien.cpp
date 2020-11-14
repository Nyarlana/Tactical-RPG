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

Alien::Alien(int max_LP, int xPos, int yPos, int speed, int targetCheckArea, int threatfulTargetCheckArea) : Fighter(max_LP, xPos, yPos, speed, targetCheckArea, threatfulTargetCheckArea), hasAggressiveBehavior(threatfulTargetCheckArea!=-1), isAKiller(false)
{
    //ctor
}

//inherited functions
void Alien::on_Notify(Component* subject, Event event)
{

}

void Alien::_init()
{
    Entity::state = SEARCH;

    if(!texture.loadFromFile("data/entities/alien.png"))
    {
      if(!texture.loadFromFile("../data/entities/alien.png"))
      {
        std::cout << "erreur" << '\n';
      }
    }

    sprite.setTexture(texture);
    sprite.setTextureRect(sf::IntRect(0,0,32,32));
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

void Alien::check()
{
    checkTargets();

    if(targets.empty())
        state = SEARCH;
    else
        state = OFFENSIVE;

    std::cout << (state==SEARCH?"searching...blabla":"FIIIGHT") << '\n';
}

void Alien::action()
{
    switch(state)
    {
        case SEARCH:
        {
            if(isAKiller && !path.empty())
                std::cout << "last of "<< path.size() <<": "<<path.back().x<<","<<path.back().y << '\n';

            if(path.empty())
                notify(this, E_GET_RANDOM_PATH);

            moveTo(path.back());
            path.pop_back();
            break;
        }
        case OFFENSIVE:
        {
            shared_ptr<Entity> t = getTopTarget();
            t->tostring();

            if(getDistanceTo(t)<2)
            {
                attack(t);
            }
            else
            {
                if(target_distance < getDistanceTo(t))
                    notify(this, E_GET_PATH_E_TARGET);

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

void Alien::answer_radar(std::shared_ptr<Entity> e)
{
    if(e.get()!=this && !isDead())
    {
        shared_ptr<Entity> me = std::dynamic_pointer_cast<Entity>(Observer::shared_from_this());
        e->add(false,me);
    }
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
            isAKiller = true;
            path.clear();
        }
    }
}

void Alien::checkTargets()
{
    Fighter::checkTargets();

    if(hasAggressiveBehavior)
    {
        notify(this, E_LF_ROV);

        for(int i=0; i<rov.size(); i++)
        {
            if(getDistanceTo(rov[i])<=targetCheckArea)
            {
                increaseThreat(rov[i], 0);
            }
        }

        rov.clear();
    }
}

void Alien::tostring()
{
    std::cout<<"j'suis un alien"<<std::endl;
}
