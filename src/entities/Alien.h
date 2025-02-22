/**@file Alien header*/
#ifndef ALIEN_H
#define ALIEN_H

#include "Fighter.h"

#include "../gameManager/Observer.h"
#include "../gameManager/Parameters.h"

#include <SFML/Graphics.hpp>
#include <SFML/Main.hpp>
#include <string>

/**@class Alien class
@brief Type of Entity meant to annoy Rovers*/
class Alien : public Fighter
{
    public:
        /** @brief constructor */
        Alien(int max_LP = 5, int xPos = 3, int yPos = 3, int speed = 3, int group_number = -1, int targetCheckArea = 3, int threatfulTargetCheckArea = 5);

        //inherited functions
        void on_Notify(Component* subject, Event event);
        void _init();
        int stateValue();
        std::string getStateS();
        void check();
        void action();
        void die();                                                 //overrides Entity::die(), destructs itself after notifying its group of its death
        void answer_radar(std::shared_ptr<Entity> e);
        void increaseThreat(std::shared_ptr<Entity> target, int threatIncrease);
        void attack(std::shared_ptr<Entity> target);
        void checkTargets();
        std::string tostring();

        //clss functions
        /** @brief Tells if the Alien's group number
        @return the group's number*/
        int getGroup();

        /** @brief Tells if the given target is an enemy
        @parameter target shared pointer of the given target
        @return is the target an enemy ?
        */
        bool isTargetable(std::shared_ptr<Entity> target);

    protected:

    private:
        //Base type definition
        typedef Fighter super;

        //attribute
        bool hasAggressiveBehavior;         //constant, inherited through its Alien-type
        int group_number;
};

#endif // ALIEN_H
