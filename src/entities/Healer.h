/**@file Healer header*/
#ifndef HEALER_H
#define HEALER_H

#include "Fighter.h"
#include "../gameManager/Observer.h"
#include "../gameManager/Parameters.h"

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
        std::string getStateS();
        void check();
        void action();
        void answer_radar(std::shared_ptr<Entity> e);
        void increaseThreat(std::shared_ptr<Entity> target, int threatIncrease);
        void attack(std::shared_ptr<Entity> target);
        void checkTargets();
        std::shared_ptr<Entity> getTopTarget();
        std::string tostring();

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
        /** @brief gives the best target to heal */
        std::shared_ptr<Entity> getTopHealTarget(int maxSeenNeed);
        /** @brief gives the highest lp lack amount met in the heal_targets */
        int getMaxNeed();
        /** @brief action to get near a heal_target or heal it */
        void healing_action();

    protected:

    private:
        //Base type definition
        typedef Fighter super;

        //attributes
        int heal_power;
        std::unordered_map<std::shared_ptr<Entity>, int> heal_targets; //targets associated with their heal need
};

#endif // HEALER_H
