/**@file Raider header*/
#ifndef RAIDER_H
#define RAIDER_H

#include <Fighter.h>


/**@class Raider class
@brief Type of Entity meant to be able to fight against other entities*/
class Raider : public Raider
{
    public:
        /** @brief constructor */
        Raider(int xPos, int yPos);
        /** @brief destructor */
        virtual ~Raider();

        //inherited functions
        void action();
        void attack(std::shared_ptr<Entity> target);

        //Class skills
        /** @brief raises the Raider's speed */
        void speedup();
        /** @brief decreases the Raider's threat value by ?? points the Aliens see in this Raider */
        void lowProfile();

    protected:

    private:
};

#endif // RAIDER_H
