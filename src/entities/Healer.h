/**@file Healer header*/
#ifndef HEALER_H
#define HEALER_H

#include "Fighter.h"
#include "../gameManager/Observer.h"

#include <SFML/Graphics.hpp>
#include <SFML/Main.hpp>
#include <string>

/**@class Healer class
@brief Type of Entity meant to heal and protect other entities, able to fight
but hits weakly*/
class Healer : public Fighter
{
    public:
        /** @brief constructor */
        Healer(int xPos=-1, int yPos=-1); //threatfullTargetCheckArea=0
        /** @brief destructor */
        ~Healer();

        //inherited functions
        void on_Notify(Component* subject, Event event);
        void _init();
        int stateValue();
        void check();
        void action();
        void answer_radar(std::shared_ptr<Entity> e);
        void increaseThreat(std::shared_ptr<Entity> target, int threatIncrease);
        void attack(std::shared_ptr<Entity> target);
        void checkTargets();
        std::shared_ptr<Entity> getTopTarget();
        std::shared_ptr<Entity> getTopHealTarget(int maxSeenNeed);
        int getMaxNeed();

        //Class skills
        /** @brief set heal need of a specific target, if the target isn't
        already is the target list and needs at least 1 lp, adds it to the list
        @param target target thats need of heal is set
        @param value amount of point by which a target needs heal*/
        void setNeed(std::shared_ptr<Entity> heal_target, int value);
        /** @brief heals the target's life points by ?? points
        @param target target that will get a heal*/
        void heal(std::shared_ptr<Entity> heal_target);
        /** @brief looks for targets in its areas and erases targets outside
        them */
        void checkHealTargets();
        void healing_action();
        void tostring();

    protected:

    private:
        //Base type definition
        typedef Fighter super;

        //attributes
        int heal_power;
        std::unordered_map<std::shared_ptr<Entity>, int> heal_targets; //targets associated with their threat level
};

#endif // HEALER_H
