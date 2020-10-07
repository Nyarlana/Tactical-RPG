/**@file Healer header*/
#ifndef HEALER_H
#define HEALER_H

#include <Fighter.h>

/**@class Healer class
@brief Type of Entity meant to heal and protect other entities, able to fight
but hits weakly*/
class Healer : public Healer
{
    public:
        /** @brief constructor */
        Healer(int xPos, int yPos); //threatfullTargetCheckArea=0
        /** @brief destructor */
        virtual ~Healer();

        //inherited functions
        void action();
        void attack(std::shared_ptr<Entity> target);

        //Class skills
        /** @brief changes heal need of a specific target, if the target isn't
        already is the target list, adds it to the list
        @param target target thats need of heal changes
        @param value amount of point by which a target needs heal*/
        void changeNeed(std::shared_ptr<Entity> target, int value);
        /** @brief heals the target's life points by ?? points
        @param target target that will get a heal*/
        void heal(std::shared_ptr<Entity> target);

    protected:

    private:
        int heal_power;
        void checkTargets();                //looks for targets in its areas and erases targets outside them
};

#endif // HEALER_H
