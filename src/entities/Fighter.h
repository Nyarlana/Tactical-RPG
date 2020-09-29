#ifndef FIGHTER_H
#define FIGHTER_H

#include <Entity.h>
#include <unordered_map>
#include <memory>

class Fighter : public Entity
{
    public:
        Fighter(int lp, int xPos, int yPos, int speed, int targetCheckArea, int threatfullTargetCheckArea);
        virtual void action();
        void moveOut();
        *std::unordered_map<std::shared_ptr<Entity>, int> getTargets();                   //gives access to target list
        void increaseThreat(std::shared_ptr<Entity> target, int threatIncrease);   //increases threat of a specific target, if the target isn't already is the target list, adds it to the list
        virtual void attack();
        virtual ~Fighter();

    protected:

    private:
        std::unordered_map<std::shared_ptr<Entity>, int> targets; //targets associated with their threat level
        int  targetCheckArea;               //radius within which checkTarget() will look for targets
        int  threatfullTargetCheckArea;     //radius within which checkTarget() will look for threatful targets

        void checkTargets();                //looks for targets in its areas and erases targets outside them
};

#endif // FIGHTER_H
