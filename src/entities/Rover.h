/**@file Rover header*/
#ifndef Rover_H
#define Rover_H

#include "Entity.h"

/**@class Rover class
@brief Rover type of Entity*/
class Rover : public Entity
{
    public:
        /** @brief constructor */
        Rover(int max_LP, int xPos, int yPos, int speed);

        //inherited functions
        virtual double operator() () = 0;
        void die();

    protected:

    private:
        //Base type definition
        typedef Entity super;
};

#endif // Rover_H
