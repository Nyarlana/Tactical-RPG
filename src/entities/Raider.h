/**@file Raider header*/
#ifndef RAIDER_H
#define RAIDER_H

#include "Fighter.h"
#include "../gameManager/Observer.h"

#include <SFML/Graphics.hpp>
#include <SFML/Main.hpp>

/**@class Raider class
@brief Type of Entity meant to be able to fight against other entities*/
class Raider : public Fighter
{
    public:
        /** @brief constructor */
        Raider(int xPos=-1, int yPos=-1);
        /** @bref destructor */
        ~Raider();

        //inherited functions
        void on_Notify(Component* subject, Event event);
        void _init();
        void _update();
        void _draw(sf::RenderWindow & window);
        int stateValue();
        std::string getStateS();
        void check();
        void action();
        void answer_radar(std::shared_ptr<Entity> e);
        void increaseThreat(std::shared_ptr<Entity> target, int threatIncrease);
        void attack(std::shared_ptr<Entity> target);
        void checkTargets();

        //Class skills
        /** @brief raises the Raider's speed */
        void speedup();
        /** @brief decreases the Raider's threat value by ?? points the Aliens see in this Raider */
        void lowProfile();
        std::string tostring();

    protected:

    private:
        //Base type definition
        typedef Fighter super;
        UI_Point point;
};

#endif // RAIDER_H
