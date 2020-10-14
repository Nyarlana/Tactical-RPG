/**@file RoverBase header*/
#ifndef RoverBase_H
#define RoverBase_H

#include "Entity.h"
#include <SFML/Graphics.hpp>
#include <SFML/Main.hpp>

/**@class RoverBase class
@brief RoverBase type of Entity*/
class RoverBase : public Entity
{
    public:
        /** @brief constructor */
        RoverBase();

        //inherited functions
        void _init();
        void _update();
        void _draw(sf::RenderWindow & window);
        void action();
        void moveOut(); //doesn't move at all
        void missionComplete();//call to all Rovers to come back with timeOut
                               //until notifying the GameManager that the game is over
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
        int objective;
        int ore_amount;
};

#endif // RoverBase_H
