/**@file Explorer header*/
#ifndef Explorer_H
#define Explorer_H

#include "Rover.h"

/**@class Explorer class
@brief Explorer type of Rover*/
class Explorer : public Rover
{
    public:
        /** @brief constructor */
        Explorer(int max_LP, int xPos, int yPos, int speed);

        //inherited functions
        virtual void action() = 0;
        void moveOut();
        void die();

    protected:


    private:
        //Base type definition
        typedef Rover super;
};

#endif // Explorer_H
