/**@file Tank header*/
#ifndef TANK_H
#define TANK_H

#include "Fighter.h"

#include "../gameManager/Observer.h"
#include "Alien.h"

#include <SFML/Graphics.hpp>
#include <SFML/Main.hpp>

#include <memory>

/**@class Tank class
@brief Type of Entity meant to be able to fight against other entities*/
class Tank : public Fighter
{
    public:
        /** @brief constructor */
        Tank(int xPos=-1, int yPos=-1);
        /** @brief destructor */
        ~Tank();

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
        std::string tostring();

        //Class skills
        /** @brief increases by ?? points the threat Aliens around see in this Tank */
        void tease();
        /** @brief multiplies by ?? the threat the selected Alien see in this Tank */
        void taunt(std::shared_ptr<Alien> alien);

    protected:

    private:
        //Base type definition
        typedef Fighter super;
};

#endif // TANK_H
