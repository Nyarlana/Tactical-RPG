#include "Entity.h"

#include <vector>
#include <chrono>
#include <iostream>
#include <thread>

using namespace std;

Entity::Entity(int _max_LP, int _xPos, int _yPos, int _speed) : max_LP(_max_LP),
    lp(_max_LP), pos(sf::Vector2i(_xPos, _yPos)), speed(_speed), target_distance(0),
    path(std::vector<sf::Vector2i>())//, pb(new UI_ProgressBar(sf::Vector2i(pos.x*32+4, pos.y*32), sf::Vector2i(24, 2), 2, max_LP, lp, sf::Color::Red, sf::Color::Green, sf::Color::Black))
{
  clock = make_shared<sf::Clock>();
  last_pause = clock->restart().asMilliseconds();
}

void Entity::_update()
{
    if(lp>0)
    {
        bool estDebout = (clock->getElapsedTime().asMilliseconds() % 1000) >= ANIM_TIME;
        int state_value = stateValue(); //à ajouter à la place du 0 quand il y aura suffisamment d'images
        //pb->_update();
        sprite.setTextureRect(sf::IntRect(estDebout*32,0*32,32,32));
    }
}

void Entity::_draw(sf::RenderWindow & window)
{
    if(lp>0 && pos.x!=-1)
    {
        window.draw(sprite);
        //pb->_draw(window);
    }
}

sf::Vector2i Entity::getPos()
{
    return pos;
}

sf::Vector2i Entity::getTopTargetPos()
{
    return top_target;
}

int Entity::getDistanceTo(std::shared_ptr<Entity> e)
{
    return getDistanceTo(e->getPos());
}

int Entity::getDistanceTo(sf::Vector2i other_pos)
{
    int x = other_pos.x-pos.x;
    int y = other_pos.y-pos.y;

    return (int) sqrt(x*x+y*y);
}

int Entity::lacksLP()
{
    if(!isDead())
        return max_LP-lp;
    else
        return -1;
}

void Entity::setPos(sf::Vector2i newPos)
{
    pos = newPos;
    std::cout << "pos reçue : "<<pos.x<<","<<pos.y << '\n';
    //pb->set_Position(sf::Vector2i(pos.x*32+4, pos.y*32));
}

void Entity::setTopTarget(sf::Vector2i pos)
{
    top_target = pos;
}

void Entity::setPath(std::vector<sf::Vector2i> new_path)
{
    path = new_path;
    for (size_t i = 0; i < path.size(); i++)
    {
        std::cout << "path " << i <<" : "<< path.back().x<<","<<path.back().y << '\n';
    }
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
    else
    {
        if(lp>max_LP)
        {
            lp = max_LP;
        }

        //pb->set_Value(lp);
        notify(this,E_LP_CHANGED);
    }
}

void Entity::die()
{
    std::cout<<"Deleted at "<<pos.x<<", "<<pos.y<<std::endl;
    lp = 0;
    notify(this, E_DIED);
    deactivate();
}

void Entity::add(bool isRov, std::shared_ptr<Entity> e)
{
    bool is_already_in = false;

    if(isRov)
    {
        for(int i=0; i<rov.size(); i++)
            if(e==rov[i])
                is_already_in=true;

        if(!is_already_in)
            rov.push_back(e);
    }
    else
    {
        for(int i=0; i<al.size(); i++)
            if(e==al[i])
                is_already_in=true;

        if(!is_already_in)
            al.push_back(e);
    }
}

void Entity::moveTo(sf::Vector2i newPos)
{
    int x = newPos.x-pos.x;
    int y = newPos.y-pos.y;

    bool distanceOk = ((int) sqrt(x*x+y*y))==1;

    if(distanceOk)
    {
        pos = newPos;
        //pb->set_Position(sf::Vector2i(pos.x*32+4, pos.y*32));
    }
}

void Entity::pause()
{
    int new_pause = clock->getElapsedTime().asMilliseconds();
    delta_pause = new_pause - last_pause;
    std::this_thread::sleep_for (std::chrono::milliseconds((2000/speed)));
    last_pause = new_pause;
}

Entity::~Entity()
{
}
