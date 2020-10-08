#include "Fighter.h"

#include <shared_ptr>
#include <vector>

using namespace std;

Fighter::Fighter() : Entity(max_LP, xPos, yPos, speed), targetCheckArea(targetCheckArea), threatfulTargetCheckArea(threatfulTargetCheckArea)
{

}

Fighter::getTargets()
{
    unordered_map<shared_ptr<Entity>, int> *ptr = targets;

    return ptr;
}

Fighter::increaseThreat(shared_ptr<Entity> target, int threatIncrease)
{
    unordered_map<shared_ptr<Entity>, int>::const_iterator got = targets.find (target);

    if ( got == targets.end() )
        targets.emplace (target, threatIncrease);
    else
        targets[got->first]+=threatIncrease;
}

Fighter::checkTargets()
{
    bool is_threatful;
    int max_distance;
    vector<shared_ptr<Entity>> to_remove;

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
            to_remove.pushback(it->first);
    }

    for ( auto it = to_remove.cbegin(); it != to_remove.cend(); ++it )
    {
        targets.erase(it);
    }

    //asking map for vector<shared_ptr<Entity>> within circle :
    //   O point = (this.xPos, this.yPos) and radius = targetCheckArea
    //then adds them to targets with 0 as threat
}
