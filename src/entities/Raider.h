/**@file Raider header*/
#ifndef RAIDER_H
#define RAIDER_H

#include "Fighter.h"
#include <SFML/Graphics.hpp>
#include <SFML/Main.hpp>

/**@class Raider class
@brief Type of Entity meant to be able to fight against other entities*/
class Raider : public Fighter
{
    public:
        /** @brief constructor */
        Raider(int xPos, int yPos);
        /** @bref destructor */
        ~Raider();

        //inherited functions
        void _init();
        void _update();
        void _draw(sf::RenderWindow & window);
        void action();
        void moveOut();
        void attack(std::shared_ptr<Entity> target);

        //Class skills
        /** @brief raises the Raider's speed */
        void speedup();
        /** @brief decreases the Raider's threat value by ?? points the Aliens see in this Raider */
        void lowProfile();

    protected:

    private:
        //Base type definition
        typedef Fighter super;
};

#endif // RAIDER_H
