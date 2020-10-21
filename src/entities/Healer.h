/**@file Healer header*/
#ifndef HEALER_H
#define HEALER_H

#include "Fighter.h"
#include <SFML/Graphics.hpp>
#include <SFML/Main.hpp>

/**@class Healer class
@brief Type of Entity meant to heal and protect other entities, able to fight
but hits weakly*/
class Healer : public Fighter
{
    public:
        /** @brief constructor */
        Healer(int xPos, int yPos); //threatfullTargetCheckArea=0
        /** @brief destructor */
        ~Healer();

        //inherited functions
        void _init();
        void _update();
        void _draw(sf::RenderWindow & window);
        double operator() ();
        void moveOut();
        void attack(std::shared_ptr<Entity> target);

        //Class skills
        /** @brief changes heal need of a specific target, if the target isn't
        already is the target list, adds it to the list
        @param target target thats need of heal changes
        @param value amount of point by which a target needs heal*/
        void changeNeed(std::shared_ptr<Entity> heal_target, int value);
        /** @brief heals the target's life points by ?? points
        @param target target that will get a heal*/
        void heal(std::shared_ptr<Entity> heal_target);
        /** @brief looks for targets in its areas and erases targets outside
        them */
        void checkHealTargets();

    protected:

    private:
        //Base type definition
        typedef Fighter super;

        //attributes
        int heal_power;
        std::unordered_map<std::shared_ptr<Entity>, int> heal_targets; //targets associated with their threat level
};

#endif // HEALER_H
