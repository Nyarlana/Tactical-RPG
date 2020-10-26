#include "Alien.h"

#include <SFML/Graphics.hpp>

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
    Entity::state = SEARCH;
}

void Alien::_update()
{
    super::checkTargets();

    if(super::targets.empty())
        state = SEARCH;
    else //if(hasAggressiveBehavior || )
        state = OFFENSIVE;
}

void Alien::_draw(sf::RenderWindow & window)
{

}

double Alien::operator()()
{
    while (!Entity::isDead())
    {
        switch(state)
        {
            case SEARCH:
            {
                break;
            }
            case OFFENSIVE:
            {
                shared_ptr<Entity> t = getTopTarget();

                if(getDistanceTo(t)==1)
                {
                    attack(t);
                    //pause();
                }
                else
                {
                    //vector<sf::Vector2i> path = TileMap::request_path(Entity::pos,t->getPos());
                    //for(int i=0; i<Entity::speed; i++)
                    //{
                    //    moveTo(path[i]); -> implémenter le système de collision
                    //                        dans moveTo
                    //    pause();
                    //}
                }

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

void Alien::die()
{
    std::cout << "An alien just died at (" << Entity::pos.x << "," << Entity::pos.y << ")" << '\n';
}

void Alien::attack(shared_ptr<Entity> target)
{
    target->takeDamage(2);

    if (target->isDead())
    {
        targets.erase(target);
    }
}
