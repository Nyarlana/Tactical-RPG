#include "Fighter.h"

#include <memory>
#include <list>
#include <vector>

using namespace std;

Fighter::Fighter(int max_LP, int xPos, int yPos, int speed, int targetCheckArea, int threatfulTargetCheckArea) : Entity(max_LP, xPos, yPos, speed), targetCheckArea(targetCheckArea), threatfulTargetCheckArea(threatfulTargetCheckArea)
{

}

void Fighter::on_Notify(Component* subject, Event event)
{
    switch (event) {
        case E_DIED:
        {
            shared_ptr<Entity> e = std::dynamic_pointer_cast<Entity>(
                ((Entity*) subject)->shared_from_this()
            );
            unordered_map<shared_ptr<Entity>, int>::const_iterator got = targets.find(e);

            e->remove_Observer(Observer::shared_from_this());

            if(got != targets.end())
                targets.erase(got->first);

            if(targets.empty())
                state = RANDOM;
        }
    }
}

unordered_map<shared_ptr<Entity>, int> Fighter::getTargets()
{
    return targets;
}

std::shared_ptr<Entity> Fighter::getTopTarget()
{
    if(!targets.empty())
    {
        shared_ptr<Entity> t  = nullptr;
        int maxRelativeThreat = 0;
        int relativeThreat;

        for ( auto it = targets.cbegin(); it != targets.cend(); ++it )
        {
            relativeThreat = targets[it->first]/getDistanceTo(it->first);

            if(t == nullptr || relativeThreat>maxRelativeThreat)
            {
                t = it->first;
                maxRelativeThreat = relativeThreat;
            }
        }

        return t;
    }

    return nullptr;
}

void Fighter::increaseThreat(shared_ptr<Entity> target, int threatIncrease)
{
    unordered_map<shared_ptr<Entity>, int>::const_iterator got = targets.find (target);

    if ( got == targets.end() )
    {
        targets.emplace (target, threatIncrease);
        target->add_Observer(Observer::shared_from_this());
    }
    else
        targets[got->first]+=threatIncrease;

    if(targets[target]==0 && getDistanceTo(target)>targetCheckArea)
    {
        targets.erase(target);
        target->remove_Observer(Observer::shared_from_this());
    }
}

void Fighter::offensive_action()
{
    std::cout << tostring() << " : action offensive" << '\n';
    shared_ptr<Entity> t = getTopTarget();

    if(TRACE_EXEC && FIGHTER_TRACE)
        std::cout << id << " : j'ai fait parler ma cible " << t->tostring() << t->getID() << '\n';
    if(getDistanceTo(t)<2)
    {
        std::cout << "j'attaque !" << '\n';
        attack(t);
    }
    else
    {
        std::cout << "je veux me rapprocher" << '\n';
        if(target_distance < getDistanceTo(t))
            notify(this, E_GET_PATH_E_TARGET);

        std::cout << "je clean le chemin" << '\n';
        if(!path.empty())
        {
            if(pos.x == path.back().x && pos.y == path.back().y)
                path.pop_back();

            if(!path.empty())
            {
                std::cout << "allez je move !" << '\n';
                move();
            }
        }

        target_distance = getDistanceTo(t);
    }
}

void Fighter::checkTargets()
{
    bool is_threatful;
    int max_distance;
    list<shared_ptr<Entity>> to_remove;

    for ( auto it = targets.cbegin(); it != targets.cend(); ++it )
    {
        is_threatful = true;

        if(targets[it->first]==0)
            is_threatful = false;

        if(is_threatful)
            max_distance = threatfulTargetCheckArea;
        else
            max_distance = targetCheckArea;

        if(getDistanceTo(it->first)>max_distance)
            to_remove.push_back(it->first);
    }

    while(!to_remove.empty())
    {
        targets.erase(to_remove.front());
        to_remove.pop_front();
    }

    //asking map for vector<shared_ptr<Entity>> within circle :
    //   O point = (this.xPos, this.yPos) and radius = targetCheckArea
    //then adds them to targets with 0 as threat
}
