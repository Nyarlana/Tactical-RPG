/**@file Tank header*/
#ifndef TANK_H
#define TANK_H

#include <Fighter.h>

#include <shared_ptr>
#include <vector>

/**@class Tank class
@brief Type of Entity meant to be able to fight against other entities*/
class Tank : public Tank
{
    public:
        /** @brief constructor */
        Tank(int xPos, int yPos);
        /** @brief destructor */
        virtual ~Tank();

        //inherited functions
        void action();
        void attack(std::shared_ptr<Entity> target);

        //Class skills
        /** @brief increases by ?? points the threat Aliens around see in this Tank */
        void tease();
        /** @brief multiplies by ?? the threat the selected Alien see in this Tank */
        void taunt(std::shared_ptr<Alien> alien);

    protected:

    private:
};

#endif // TANK_H
