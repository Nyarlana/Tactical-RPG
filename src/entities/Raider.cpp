#include "Raider.h"

#include "Alien.h"

#include <memory>
#include <vector>

using namespace std;

Raider::Raider(int xPos, int yPos) : Fighter(6, xPos, yPos, 4, 3, 4), point(pos, sf::Color::Black)
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
    Entity::state = OUTER;

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

void Raider::_update()
{
    Entity::_update();
    point.set_Position(sf::Vector2i(32*pos.x+14,32*pos.y+14));
}

void Raider::_draw(sf::RenderWindow & window)
{
    Entity::_draw(window);

    point._draw(window);
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

std::string Raider::getStateS()
{

    std::string the_string;

    switch (Entity::state)
    {
        case OUTER:
            the_string = "OUTER"; break;
        case EXPLORATION:
            the_string = "EXPLORATION"; break;
        case OFFENSIVE:
            the_string = "OFFENSIVE"; break;
        case END_GAME:
            the_string = "END_GAME"; break;
        default:
            the_string = "ERROR";
    }

    the_string += " : " + std::to_string(targets.size());
    return the_string;
}

void Raider::check()
{
    if(state!=OUTER && state!=END_GAME)
    {
        checkTargets();

        if(targets.empty())
            state = EXPLORATION;
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

            move();
            break;
        }
        case OFFENSIVE:
        {
            offensive_action();
            break;
        }
        case END_GAME:
        {
            if(TRACE_EXEC && RAIDER_TRACE)
                std::cout << "mission complete : back to rover base" << '\n';
            if(path.size() >= 2)
            {
                move();
            }
            else
                std::cout << "arrived at roverbase" << '\n';
            break;
        }
        default:
        {
            std::cout << "WTF ?" << '\n';
            state = EXPLORATION;
            break;
        }
    }
}

void Raider::answer_radar(std::shared_ptr<Entity> e)
{
    if(!isDead())
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
            path.clear();
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
            increaseThreat(al[i], 1);
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

std::string Raider::tostring()
{
    return "raider";
}
