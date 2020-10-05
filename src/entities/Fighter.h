#ifndef FIGHTER_H
#define FIGHTER_H

#include <Entity.h>
#include <unordered_map>
#include <memory>

class Fighter : public Entity
{
    public:
        //constructor
        Fighter(int xPos, int yPos);
        //destructor
        virtual ~Fighter();

        //inherited functions
        virtual void action()  = 0;
        virtual void moveOut() = 0;

        //accessor
        *std::unordered_map<std::shared_ptr<Entity>, int> getTargets();            //gives access to target list
        //modifier
        void increaseThreat(std::shared_ptr<Entity> target, int threatIncrease);   //increases threat of a specific target, if the target isn't already is the target list, adds it to the list
        //action
        virtual void attack(std::shared_ptr<Entity> target) = 0;


    protected:

    private:
        std::unordered_map<std::shared_ptr<Entity>, int> targets; //targets associated with their threat level
        int  targetCheckArea;               //radius within which checkTarget() will look for targets
        int  threatfulTargetCheckArea;     //radius within which checkTarget() will look for threatful targets

        void checkTargets();                //looks for targets in its areas and erases targets outside them
};

#endif // FIGHTER_H
