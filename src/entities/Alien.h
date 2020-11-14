/**@file Alien header*/
#ifndef ALIEN_H
#define ALIEN_H

#include "Fighter.h"
#include "../gameManager/Observer.h"

#include <SFML/Graphics.hpp>
#include <SFML/Main.hpp>
#include <string>

/**@class Alien class
@brief Type of Entity meant to annoy Rovers*/
class Alien : public Fighter
{
    public:
        /** @brief constructor */
        Alien(int max_LP = 5, int xPos = 3, int yPos = 3, int speed = 3, int targetCheckArea = 3, int threatfulTargetCheckArea = 5);

        //inherited functions
        void on_Notify(Component* subject, Event event);
        void _init();
        int stateValue();
        void check();
        void action();
        void die();                                                 //overrides Entity::die(), destructs itself after notifying its group of its death
        void answer_radar(std::shared_ptr<Entity> e);
        void increaseThreat(std::shared_ptr<Entity> target, int threatIncrease);
        void attack(std::shared_ptr<Entity> target);
        void checkTargets();
        void tostring();

    protected:

    private:
        //Base type definition
        typedef Fighter super;

        //attribute
        bool hasAggressiveBehavior;         //constant, inherited through its Alien-type
        bool isAKiller;
};

#endif // ALIEN_H
