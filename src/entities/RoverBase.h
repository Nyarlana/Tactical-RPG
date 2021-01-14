/**@file RoverBase header*/
#ifndef ROVER_BASE_H
#define ROVER_BASE_H

#include "entities.h"
#include "../UI/UI.h"

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
        void add_Observer_and_Rovers(std::shared_ptr<Observer> obs);
        void _init();
        void _update();
        void _draw(sf::RenderWindow & window);
        int stateValue();
        std::string getStateS();
        void check();
        void action();
        int getOreAmount();
        int getObjective();
        void die(); //kills all Rovers and notifies the GameManager that the
                    //game is over
        void answer_radar(std::shared_ptr<Entity> e);
        std::string tostring();

        //class skills
        /** @brief Sets all the Rovers to END_GAME state so they come back to the base */
        void missionComplete();//call to all Rovers to come back with timeOut
                               //until notifying the GameManager that the game is over
        /** @brief Parsing method to return a mission based on a file called "mission".txt */
        static RoverBase launchMission(std::string mission);
        /** @brief adds one ore to the account */
        void getOneOre();

    protected:

    private:
        //Base type definition
        typedef Entity super;
        std::vector<sf::Vector2i> path;
        int objective;
        int ore_amount;
        std::vector<std::shared_ptr<Entity>> rovers;
        UI_Point point;
        int deads;
};


#endif // ROVER_BASE_H
