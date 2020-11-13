#include "Entity.h"

#include <vector>
#include <chrono>
#include <iostream>

using namespace std;

Entity::Entity(int _max_LP, int _xPos, int _yPos, int _speed) : max_LP(_max_LP),
    lp(_max_LP), pos(sf::Vector2i(_xPos, _yPos)), speed(_speed), target_distance(0),
    path(std::vector<sf::Vector2i>())
{
  clock = make_shared<sf::Clock>();
}

void Entity::_update()
{

    bool estDebout = (clock->getElapsedTime().asMilliseconds() % 1000) >= ANIM_TIME;

    int state_value = stateValue(); //à ajouter à la place du 0 quand il y aura suffisamment d'images

    sprite.setTextureRect(sf::IntRect(estDebout*32,0*32,32,32));
}

void Entity::_draw(sf::RenderWindow & window)
{
    sprite.setPosition(pos.x*32,pos.y*32);
    window.draw(sprite);
}

sf::Vector2i Entity::getPos()
{
    return pos;
}

sf::Vector2i Entity::getTopTargetPos()
{
    return top_target;
}

int Entity::getDistanceTo(shared_ptr<Entity> e)
{
    int x = e.get()->getPos().x-pos.x;
    int y = e.get()->getPos().y-pos.y;

    return (int) sqrt(x*x+y*y);
}

void Entity::setPos(sf::Vector2i newPos)
{
    pos = newPos;
}

void Entity::setTopTarget(sf::Vector2i pos)
{
    top_target = pos;
}

void Entity::setPath(std::vector<sf::Vector2i> new_path)
{
    path = new_path;
}

bool Entity::isDead()
{
    return lp<1;
}

void Entity::takeDamage(int value) //critical section
{
    lp-=value;

    //notify taken damage
    std::cout<<"An Entity took "<<value<<" damages\n";

    if(lp<=0)
    {
        die();
    }
    else if(lp>max_LP)
    {
        lp = max_LP;
    }
}

void Entity::die()
{
    std::cout<<"Deleted at "<<pos.x<<", "<<pos.y<<std::endl;
    deactivate();
}

void Entity::moveTo(sf::Vector2i newPos)
{
    int x = newPos.x-pos.x;
    int y = newPos.y-pos.y;

    bool distanceOk = ((int) sqrt(x*x+y*y))==1;

    if(distanceOk)
    {
        pos = newPos;
    }
}

void Entity::pause()
{
    int new_pause = clock->getElapsedTime().asMilliseconds();
    delta_pause = new_pause - last_pause;
    // cout<<((1000/speed)/*-delta_pause*/)<<endl;
    std::this_thread::sleep_for (std::chrono::milliseconds((1000/speed)));
    last_pause = new_pause;
}

Entity::~Entity()
{
}
