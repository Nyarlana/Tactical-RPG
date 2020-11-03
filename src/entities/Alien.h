/**@file Alien header*/
#ifndef ALIEN_H
#define ALIEN_H

#include "Fighter.h"
#include "../gameManager/Observer.h"

#include <SFML/Graphics.hpp>
#include <SFML/Main.hpp>

/**@class Alien class
@brief Type of Entity meant to annoy Rovers*/
class Alien : public Fighter
{
    public:
        /** @brief constructor */
        Alien(int max_LP, int xPos, int yPos, int speed, int targetCheckArea, int threatfulTargetCheckArea, bool hasAggressiveBehavior);

        //inherited functions
        void on_Notify(const Component* subject, Event event);
        void _init();
        int stateValue();
        void action();
        void die();                                                 //overrides Entity::die(), destructs itself after notifying its group of its death
        void increaseThreat(std::shared_ptr<Entity> target, int threatIncrease);
        void attack(std::shared_ptr<Entity> target);

    protected:

    private:
        //Base type definition
        typedef Fighter super;

        //attribute
        bool hasAggressiveBehavior;         //constant, inherited through its Alien-type
};

#endif // ALIEN_H
