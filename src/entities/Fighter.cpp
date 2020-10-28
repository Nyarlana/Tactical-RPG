#include "Fighter.h"

#include <memory>
#include <list>
#include <vector>

using namespace std;

Fighter::Fighter(int max_LP, int xPos, int yPos, int speed, int targetCheckArea, int threatfulTargetCheckArea) : Entity(max_LP, xPos, yPos, speed), targetCheckArea(targetCheckArea), threatfulTargetCheckArea(threatfulTargetCheckArea)
{

}

unordered_map<shared_ptr<Entity>, int> Fighter::getTargets()
{
    //unordered_map<shared_ptr<Entity>, int> *ptr;
    //ptr = targets;

    return targets;
}

std::shared_ptr<Entity> Fighter::getTopTarget()
{
    if(!targets.empty())
    {
        shared_ptr<Entity> t = nullptr;
        int  maxSeenThreat   = 0;

        for ( auto it = targets.cbegin(); it != targets.cend(); ++it )
        {
            if(t == nullptr || targets[it->first]>maxSeenThreat)
            {
                t = it->first;
                maxSeenThreat = targets[it->first];
            }
            else if(targets[it->first]==maxSeenThreat &&
                    getDistanceTo(it->first)<getDistanceTo(t))
            {
                t = it->first;
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
        targets.emplace (target, threatIncrease);
    else
        targets[got->first]+=threatIncrease;

    if(targets[got->first]==0)
        targets.erase(got->first);
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
