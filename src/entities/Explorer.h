/**@file Explorer header*/
#ifndef Explorer_H
#define Explorer_H

#define MAX_SIZE_X 25
#define MAX_SIZE_Y 25

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
        void die();

        //Class skills
        /* @brief
        */
        void explore();
        void completeMap();
    protected:
        int[MAX_SIZE_X][MAX_SIZE_Y] map;

    private:
        //Base type definition
        typedef Rover super;
};

#endif // Explorer_H
