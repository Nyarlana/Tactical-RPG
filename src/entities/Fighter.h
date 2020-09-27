#ifndef FIGHTER_H
#define FIGHTER_H

#include <Entity.h>


class Fighter : public Entity
{
    public:
        Fighter(int lp, int xPos, int yPos, int speed, int targetCheckArea, int threatfullTargetCheckArea);
        void action();
        *unordered_map<Entity, int> getTargets();                   //gives access to target list
        void increaseThreat(Entity* target, int threatIncrease);   //increases threat of a specific target, if the target isn't already is the target list, adds it to the list
        void attack();
        virtual ~Fighter();

    protected:

    private:
        unordered_map<Entity, int> targets; //targets asociated with their threat level
        int  targetCheckArea;               //radius within which checkTarget() will look for targets
        int  threatfullTargetCheckArea;     //radius within which checkTarget() will look for threatful targets

        void checkTargets();                //looks for targets in its areas and erases targets outside them
};

#endif // FIGHTER_H
