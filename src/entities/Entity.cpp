#include "Entity.h"

#include <vector>
#include <chrono>
#include <iostream>
#include <thread>

using namespace std;

Entity::Entity(int _max_LP, int _xPos, int _yPos, int _speed) : max_LP(_max_LP),
    lp(_max_LP), pos(sf::Vector2i(_xPos, _yPos)), speed(_speed), target_distance(0),
    path(std::vector<sf::Vector2i>()),
    pb(new UI_ProgressBar(sf::Vector2i(_xPos, _yPos), sf::Vector2i(28,2), 2, _max_LP, _max_LP)),
    tb(new UI_TextBox(sf::Vector2i(_xPos, _yPos), "state", 12, sf::Vector2i(2,2), sf::Color::White, sf::Color(0,0,0,100), "data/font.ttf")),
    id(entity_number++), m(new std::mutex())
{
    clock = make_shared<sf::Clock>();
    last_pause = clock->restart().asMilliseconds();
    if(TRACE_EXEC && ENTITY_TRACE)
        std::cout << id << '\n';
}

void Entity::_update()
{
    if(lp>0)
    {
        bool estDebout = (clock->getElapsedTime().asMilliseconds() % 1000) >= ANIM_TIME;
        int state_value = stateValue();
        sprite.setTextureRect(sf::IntRect(estDebout*32,0*32,32,32));
        pb->set_Position(sf::Vector2i(pos.x*32+2, pos.y*32));
        pb->_update();
        tb->set_Position(sf::Vector2i(pos.x*32+6, pos.y*32+10));
        tb->setText(getStateS());
        tb->_update();
    }
}

void Entity::_draw(sf::RenderWindow & window)
{
    if(lp>0 && pos.x!=-1)
    {
        sprite.setPosition(pos.x*32, pos.y*32);
        window.draw(sprite);
        pb->_draw(window);
        tb->_draw(window);
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
    if(!e->isDead())
        return getDistanceTo(e->getPos());
    return 1000000;
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
    if(!path.empty())
        path.pop_back();
    pos = newPos;
}

sf::Vector2i Entity::getNextPos()
{
    if(!path.empty())
        return path.back();

    return sf::Vector2i(-1,-1);
}

void Entity::setTopTarget(sf::Vector2i pos)
{
    top_target = pos;
}

void Entity::setState(State s)
{
    state = s;
}

void Entity::setPath(std::vector<sf::Vector2i> new_path)
{
    path = new_path;
}

bool Entity::isDead()
{
    return lp<1;
}

int Entity::getID()
{
    return id;
}

void Entity::takeDamage(int value) //critical section
{
    m->lock();

    if(lp>0)
    {
        lp-=value;

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

            pb->substract_Value(value);
            notify(this,E_LP_CHANGED);
            if(TRACE_EXEC && ENTITY_TRACE)
                std::cout << "lp left = "<<lp << '\n';
        }
    }

    m->unlock();
}

void Entity::die()
{
    tostring();
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

void Entity::move()
{
    if(!path.empty())
        notify(this, E_MOVE);
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
