#include "entities.h"

#include <SFML/Graphics.hpp>

#include <memory>
#include <vector>
#include <iostream>

using namespace std;

Alien::Alien(int max_LP, int xPos, int yPos, int speed, int group_number, int targetCheckArea, int threatfulTargetCheckArea) : Fighter(max_LP, xPos, yPos, speed, targetCheckArea, threatfulTargetCheckArea), group_number(group_number), hasAggressiveBehavior(threatfulTargetCheckArea!=-1)
{
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

std::string Alien::getStateS()
{
    std::string the_string;

    switch (state)
    {
        case SEARCH:
            the_string = "SEARCH"; break;
        case OFFENSIVE:
            the_string = "OFFENSIVE"; break;
        default:
            the_string = "ERROR";
    }

    the_string += " : " + std::to_string(targets.size());
    return the_string;
}

void Alien::check()
{
    checkTargets();

    if(targets.empty())
        state = SEARCH;
    else
        state = OFFENSIVE;
}

void Alien::action()
{
    switch(state)
    {
        case SEARCH:
        {
            if(path.empty())
                notify(this, E_GET_RANDOM_PATH);

            move();
            break;
        }
        case OFFENSIVE:
        {
            shared_ptr<Alien> t = dynamic_pointer_cast<Alien>(getTopTarget());
            if(t != nullptr)
                std::cout << "coucou je cible un alien" << '\n';
            else
                std::cout << "coucou je cible PAS un alien" << '\n';
            std::cout << "ma cible est déclarée" << '\n';
            offensive_action();
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
    if(!isDead())
    {
        shared_ptr<Entity> me = std::dynamic_pointer_cast<Entity>(Observer::shared_from_this());
        e->add(false,me);
    }
}

void Alien::increaseThreat(shared_ptr<Entity> target, int threatIncrease)
{
    if(isTargetable(target))
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
    if(isTargetable(target))
    {
        target->takeDamage(2);

        if (target->isDead())
            path.clear();
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
                increaseThreat(rov[i], 2);
            }
        }

        rov.clear();

        notify(this, E_LF_AL);

        for(int i=0; i<al.size(); i++)
        {
            if(getDistanceTo(al[i])<=targetCheckArea)
            {
                if(isTargetable(al[i]))
                    increaseThreat(al[i], 1);
            }
        }

        al.clear();
    }
}

bool Alien::isTargetable(shared_ptr<Entity> target)
{
    shared_ptr<Alien> t = dynamic_pointer_cast<Alien>(target);

    if(t!=nullptr && (id==t->getID() || t->getGroup()==group_number))
        return false;

    return true;
}

int Alien::getGroup()
{
    return group_number;
}

std::string Alien::tostring()
{
    return "alien";
}
