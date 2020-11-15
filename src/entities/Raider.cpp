#include "Raider.h"

#include "Alien.h"

#include <memory>
#include <vector>

using namespace std;

Raider::Raider(int xPos, int yPos) : Fighter(6, xPos, yPos, 4, 3, 4)
{
    //ctor
}

Raider::~Raider()
{
    //dtor
}

//inherited functions
void Raider::on_Notify(Component* subject, Event event)
{

}

void Raider::_init()
{
    super::state = OUTER;

    // if(!texture.loadFromFile("data/entities/raider.png"))
    // {
    //   if(!texture.loadFromFile("../data/entities/raider.png"))
    //   {
    //     std::cout << "erreur" << '\n';
    //   }
    // }
    //
    // sprite.setTexture(texture);
    // sprite.setTextureRect(sf::IntRect(0,0,32,32));
}

int Raider::stateValue()
{
    int value;

    switch (Entity::state)
    {
        case OUTER:
        {
            value = 0;
            break;
        }
        case EXPLORATION:
        {
            value = 1;
            break;
        }
        case OFFENSIVE:
        {
            value = 2;
            break;
        }
        case END_GAME:
        {
            value = 3;
            break;
        }
        default:
        {
            value = -1;
        }
    }

    return value;
}

void Raider::check()
{
    if(state!=OUTER && state!=END_GAME)
    {
        checkTargets();

        if(targets.empty())
            state = SEARCH;
        else
            state = OFFENSIVE;
    }
}

void Raider::action()
{
    switch(state)
    {
        case OUTER:
        {
            notify(this, E_OUT_REQ);
            while (pos.x==-1) {
                pause();
                std::cout << "raider is waiting..." << '\n';
            }
            state=EXPLORATION;
            break;
        }
        case EXPLORATION:
        {
            if(path.empty())
                notify(this, E_GET_RANDOM_PATH);

            moveTo(path.back());
            path.pop_back();
            break;
        }
        case OFFENSIVE:
        {
            offensive_action();
            break;
        }
        case END_GAME:
        {
            break;
        }
        default:
        {
            Entity::state = EXPLORATION;
        }
    }
}

void Raider::answer_radar(std::shared_ptr<Entity> e)
{
    if(e.get()!=this && !isDead())
    {
        shared_ptr<Entity> me = std::dynamic_pointer_cast<Entity>(Observer::shared_from_this());
        e->add(true,me);
    }
}

void Raider::increaseThreat(shared_ptr<Entity> target, int threatIncrease)
{
    if(typeid(target.get())==typeid(Alien()))
    {
        super::increaseThreat(target, threatIncrease);

        if(targets.empty())
            Entity::state = EXPLORATION;
        else
            Entity::state = OFFENSIVE;
    }
}

void Raider::attack(shared_ptr<Entity> target)
{
    if(typeid(target.get())==typeid(Alien()))
    {
        target->takeDamage(5);

        if (target->isDead())
        {
            targets.erase(target);
            path.clear();
        }
    }
}

void Raider::checkTargets()
{
    Fighter::checkTargets();

    notify(this, E_LF_AL);

    for(int i=0; i<al.size(); i++)
    {
        if(getDistanceTo(al[i])<=targetCheckArea)
        {
            increaseThreat(al[i], 0);
        }
    }

    al.clear();
}

//Class skills
/** @brief raises the Raider's speed */
void Raider::speedup()
{
    speed++;
}

/** @brief decreases the Raider's threat value by ?? points the Aliens see in this Raider */
void Raider::lowProfile()
{
    //notify(this,E_LOW_PROFILE);
}

void Raider::tostring()
{
    std::cout<<"j'suis un raider"<<std::endl;
}
