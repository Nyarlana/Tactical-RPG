/**@file Protector header*/
#ifndef Protector_H
#define Protector_H

#include "Rover.h"

/**@class Protector class
@brief Protector type of Rover*/
class Protector : public Rover
{
    public:
        /** @brief constructor */
        Protector(int max_LP, int xPos, int yPos, int speed);

        //inherited functions
        virtual double operator() () = 0;
        void moveOut();
        void die();

    protected:

    private:
        //Base type definition
        typedef Rover super;
};

#endif // Protector_H
