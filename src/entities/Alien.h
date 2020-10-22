/**@file Alien header*/
#ifndef ALIEN_H
#define ALIEN_H

#include "Fighter.h"
#include "Rover.h"
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
        void _init();
        void _update();
        void _draw(sf::RenderWindow & window);
        double operator() ();
        void die();                                                 //overrides Entity::die(), destructs itself after notifying its group of its death
        void attack(std::shared_ptr<Entity> target);

    protected:

    private:
        //Base type definition
        typedef Fighter super;

        //attribute
        bool hasAggressiveBehavior;         //constant, inherited through its Alien-type
};

#endif // ALIEN_H
