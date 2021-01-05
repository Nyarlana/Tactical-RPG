#include "entities.h"

#include <memory>
#include <vector>
#include <list>

using namespace std;

Healer::Healer(int xPos, int yPos) : Fighter(8, xPos, yPos, 3, 1, 3), heal_power(2)
{}

Healer::~Healer()
{
    //dtor
}

//inherited functions
void Healer::on_Notify(Component* subject, Event event)
{
    switch (event) {
        case E_LP_CHANGED:
        {
            shared_ptr<Entity> e = std::dynamic_pointer_cast<Entity>(
                ((Entity*) subject)->shared_from_this()
            );

            setNeed(e,e->lacksLP());
            break;
        }
        case E_DIED:
        {
            Fighter::on_Notify(subject, event);

            shared_ptr<Entity> e = std::dynamic_pointer_cast<Entity>(
                ((Entity*) subject)->shared_from_this()
            );
            unordered_map<shared_ptr<Entity>, int>::const_iterator got = heal_targets.find(e);

            e->remove_Observer(Observer::shared_from_this());

            if(got != heal_targets.end())
                heal_targets.erase(got->first);

            if(!heal_targets.empty())
                state = HEAL;
        }
    }
}

void Healer::_init()
{
    Entity::state = OUTER;

    if(!texture.loadFromFile("data/entities/healer.png"))
    {
      if(!texture.loadFromFile("../data/entities/healer.png"))
      {
        std::cout << "erreur" << '\n';
      }
    }

    sprite.setTexture(texture);
    sprite.setTextureRect(sf::IntRect(0,0,32,32));
}

int Healer::stateValue()
{
    int value;

    switch (Entity::state)
    {
        case OUTER:
        {
            value = 0;
            break;
        }
        case SEARCH:
        {
            value = 1;
            break;
        }
        case PROTECTION:
        {
            value = 2;
            break;
        }
        case HEAL:
        {
            value = 3;
            break;
        }
        case OFFENSIVE:
        {
            value = 4;
            break;
        }
        case END_GAME:
        {
            value = 5;
            break;
        }
        default:
        {
            value = -1;
        }
    }

    return value;
}

std::string Healer::getStateS()
{
    std::string the_string;

    switch (Entity::state)
    {
        case OUTER:
            the_string = "OUTER"; break;
        case SEARCH:
            the_string = "SEARCH"; break;
        case PROTECTION:
            the_string = "PROTECTION"; break;
        case HEAL:
            the_string = "HEAL"; break;
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

void Healer::check()
{
    if(state!=OUTER && state!=END_GAME)
    {
        checkHealTargets();

        //add check for protected
        checkTargets();

        if(getMaxNeed()>0)
            state = HEAL;//add protect_targets
        else if(!targets.empty())
            state = OFFENSIVE;
        else
            state = SEARCH;
    }
}

void Healer::action()
{
    switch(state)
    {
        case OUTER:
        {
            notify(this, E_OUT_REQ);
            while (pos.x==-1) {
                pause();
                if(TRACE_EXEC && HEALER_TRACE)
                    std::cout << "healer is waiting..." << '\n';
            }
            state=SEARCH;
            break;
        }
        case SEARCH:
        {
            if(TRACE_EXEC && HEALER_TRACE)
                std::cout << "healer searching..." << '\n';
            if(path.empty())
                notify(this, E_GET_RANDOM_PATH);

            move();
            break;
        }
        case PROTECTION:
        {
            if(TRACE_EXEC && HEALER_TRACE)
                std::cout << "healer protecting..." << '\n';
            break;
        }
        case HEAL:
        {
            if(TRACE_EXEC && HEALER_TRACE)
                std::cout << "healer healing..." << '\n';
            healing_action();
            break;
        }
        case OFFENSIVE:
        {
            if(TRACE_EXEC && HEALER_TRACE)
                std::cout << "healer attacking..." << '\n';
            offensive_action();
            break;
        }
        case END_GAME:
        {
            if(TRACE_EXEC && HEALER_TRACE)
                std::cout << "mission complete : back to rover base" << '\n';
            if(path.empty() && pos.x!=-1)
                notify(this,E_REQ_PATH_BASE);
            /*else
            {
                moveTo(path.back());
                path.pop_back();
            }*/
            break;
        }
        default:
        {
            Entity::state = SEARCH;
        }
    }
}

void Healer::increaseThreat(shared_ptr<Entity> target, int threatIncrease)
{
    shared_ptr<Alien> t = dynamic_pointer_cast<Alien>(target);

    if(t!=nullptr)
        super::increaseThreat(target, threatIncrease);
}

void Healer::answer_radar(std::shared_ptr<Entity> e)
{
    if(!isDead())
    {
        shared_ptr<Entity> me = std::dynamic_pointer_cast<Entity>(Observer::shared_from_this());
        e->add(true,me);
    }
}

void Healer::attack(shared_ptr<Entity> target)
{
    shared_ptr<Alien> t = dynamic_pointer_cast<Alien>(target);

    if(t!=nullptr)
    {
        target->takeDamage(1);

        if (target->isDead())
        {
            targets.erase(target);
            path.clear();
        }
    }
}

void Healer::checkTargets()
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
/** @brief set heal need of a specific target, if the target isn't
already is the target list and needs at least 1 lp, adds it to the list
@param target target thats need of heal is set
@param value amount of point by which a target needs heal*/
void Healer::setNeed(shared_ptr<Entity> heal_target, int value)
{
    if(value>0)
    {
        unordered_map<shared_ptr<Entity>, int>::const_iterator got = heal_targets.find (heal_target);

        if(getDistanceTo(heal_target)>targetCheckArea*2 && got!=heal_targets.end())
        {
            heal_targets.erase(heal_target);
            heal_target->remove_Observer(Observer::shared_from_this());
        }
        else
        {
            if ( got == heal_targets.end())
                heal_targets.emplace (heal_target, value);
            else
                heal_targets[got->first]=value;
            heal_target->add_Observer(Observer::shared_from_this());
        }
    }
}

/** @brief heals the target's life points by ?? points
@param target target that will get a heal*/
void Healer::heal(std::shared_ptr<Entity> heal_target)
{
    shared_ptr<Alien> t = dynamic_pointer_cast<Alien>(heal_target);

    if(t==nullptr)
        heal_target->takeDamage(heal_power*-1);

    pause();
}

void Healer::checkHealTargets()
{
    notify(this, E_LF_ROV);

    for(int i=0; i<rov.size(); i++)
    {
        if(getDistanceTo(rov[i])<=targetCheckArea*2)
        {
            setNeed(rov[i], rov[i]->lacksLP());
        }
    }

    rov.clear();
}

void Healer::healing_action()
{
    if(TRACE_EXEC && HEALER_TRACE)
        std::cout << "\t--------healing_action-------" << '\n';
    std::shared_ptr<Entity> t = getTopTarget();

    if(getDistanceTo(t)<2)
    {
        heal(t);
    }
    else
    {
        if(target_distance < getDistanceTo(t))
            notify(this, E_GET_PATH_E_TARGET);

        move();

        target_distance = getDistanceTo(t);
    }
}

std::shared_ptr<Entity> Healer::getTopTarget()
{
    int maxSeenNeed = getMaxNeed();

    if(maxSeenNeed>0)
        return getTopHealTarget(maxSeenNeed);
    else
        return Fighter::getTopTarget();
}

std::shared_ptr<Entity> Healer::getTopHealTarget(int maxSeenNeed)
{
    shared_ptr<Entity> t = nullptr;

    for ( auto it = heal_targets.cbegin(); it != heal_targets.cend(); ++it )
    {
        if(heal_targets[it->first]>=maxSeenNeed && (t == nullptr || getDistanceTo(it->first)<getDistanceTo(t)))
        {
            t = it->first;
            maxSeenNeed = heal_targets[t];
        }
    }

    return t;
}

int Healer::getMaxNeed()
{
    int maxSeenNeed = 0;

    for ( auto it = heal_targets.cbegin(); it != heal_targets.cend(); ++it )
    {
        if(heal_targets[it->first]>maxSeenNeed)
        {
            maxSeenNeed = heal_targets[it->first];
        }
    }

    return maxSeenNeed;
}

std::string Healer::tostring()
{
    return "healer";
}
