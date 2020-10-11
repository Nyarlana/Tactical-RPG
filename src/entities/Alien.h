/**@file Alien header*/
#ifndef ALIEN_H
#define ALIEN_H

#include "Fighter.h"

/**@class Alien class
@brief Type of Entity meant to annoy Rovers*/
class Alien : public Fighter
{
    public:
        /** @brief constructor */
        Alien(int max_LP, int xPos, int yPos, int speed, int targetCheckArea, int threatfulTargetCheckArea, bool hasAggressiveBehavior);

        //inherited functions
        void action();
        void moveOut();
        void die();                                                 //overrides Entity::die(), destructs itself after notifying its group of its death
        void attack(std::shared_ptr<Entity> target);

    protected:

    private:
        bool hasAggressiveBehavior;         //constant, inherited through its Alien-type
};

#endif // ALIEN_H
