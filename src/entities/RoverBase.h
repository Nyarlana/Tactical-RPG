/**@file RoverBase header*/
#ifndef RoverBase_H
#define RoverBase_H

#include "Entity.h"

/**@class RoverBase class
@brief RoverBase type of Entity*/
class RoverBase : public Entity
{
    public:
        /** @brief constructor */
        RoverBase();

        //inherited functions
        void action();
        void moveOut(); //doesn't move at all
        void missionComplete();//notifies the GameManager that the game is over
        void die(); //kills all Rovers and notifies the GameManager that the game
                    //is over

        //
        static RoverBase launchMission(std::string mission);
        //Rovers management
        void getOneOre();
        void putRover(int rover_number, int x, int y);
        void getRover(Rover r);

    protected:

    private:
        //Base type definition
        typedef Entity super;
};

#endif // RoverBase_H
