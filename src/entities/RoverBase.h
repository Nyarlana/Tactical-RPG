/**@file RoverBase header*/
#ifndef ROVER_BASE_H
#define ROVER_BASE_H

#include "entities.h"

#include "../gameManager/Observer.h"

#include <SFML/Graphics.hpp>
#include <SFML/Main.hpp>

#include <memory>
#include <vector>

/**@class RoverBase class
@brief RoverBase type of Entity*/
class RoverBase : public Entity
{
    public:
        /** @brief constructor */
        RoverBase(int _x_pos, int _y_pos, int _objective, std::string _rovers);

        //inherited functions
        void on_Notify(Component* subject, Event event);
        void add_Observer(std::shared_ptr<Observer> obs);
        void _init();
        void _update();
        void _draw(sf::RenderWindow & window);
        int stateValue();
        void check();
        void action();
        void moveTo(sf::Vector2i newPos); //doesn't move at all
        void die(); //kills all Rovers and notifies the GameManager that the
                    //game is over
        void answer_radar(std::shared_ptr<Entity> e);

        //class skills
        void missionComplete();//call to all Rovers to come back with timeOut
                               //until notifying the GameManager that the game is over

        static RoverBase launchMission(std::string mission);
        //Rovers management
        void getOneOre();
        void putRover(int rover_number, int x, int y);
        //void getRover(Entity r);
        void takeDamage(int value);
        void tostring();

    protected:

    private:
        //Base type definition
        typedef Entity super;
        std::vector<sf::Vector2i> path;
        int objective;
        int ore_amount;
        std::vector<std::shared_ptr<Entity>> rovers;
};


#endif // ROVER_BASE_H
