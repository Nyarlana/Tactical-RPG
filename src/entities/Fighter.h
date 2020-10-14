/**@file Fighter header*/
#ifndef FIGHTER_H
#define FIGHTER_H

#include "Entity.h"

#include <unordered_map>
#include <memory>

/**@class Fighter class
  @brief Type of Entity meant to be able to fight against other entities*/
class Fighter : public Entity
{
    public:
        /** @brief constructor */
        Fighter(int max_LP, int xPos, int yPos, int speed, int targetCheckArea, int threatfulTargetCheckArea);

        //inherited functions
        virtual void action()  = 0;
        virtual void moveOut() = 0;

        //accessor
        /** @brief gives access to the target list
            @return targets*/
        std::unordered_map<std::shared_ptr<Entity>, int> getTargets();
        //modifier
        /** @brief increases threat of a specific target, if the target isn't
            already is the target list, adds it to the list
            @param target the target which will get a threat increase
            @param threatIncrease amount of threat that will be added
        */
        void increaseThreat(std::shared_ptr<Entity> target, int threatIncrease);
        //action
        /** @brief simple attack against another Entity, depending on the subclass
            of this Fighter
            @param target target that will be attacked*/
        virtual void attack(std::shared_ptr<Entity> target) = 0;


    protected:

    private:
        //Base type definition
        typedef Entity super;

        //attributes
        std::unordered_map<std::shared_ptr<Entity>, int> targets; //targets associated with their threat level
        int  targetCheckArea;               //radius within which checkTarget() will look for targets
        int  threatfulTargetCheckArea;     //radius within which checkTarget() will look for threatful targets

        void checkTargets();                //looks for targets in its areas and erases targets outside them
};

#endif // FIGHTER_H
