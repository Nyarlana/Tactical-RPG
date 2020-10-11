/**@file Tank header*/
#ifndef TANK_H
#define TANK_H

#include "Fighter.h"
#include "Alien.h"

#include <memory>
#include <vector>

/**@class Tank class
@brief Type of Entity meant to be able to fight against other entities*/
class Tank : public Fighter
{
    public:
        /** @brief constructor */
        Tank(int xPos, int yPos);

        //inherited functions
        void action();
        void moveOut();
        void attack(std::shared_ptr<Entity> target);

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
