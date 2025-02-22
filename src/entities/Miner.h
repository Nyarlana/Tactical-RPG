/**@file Miner header*/
#ifndef MINER_H
#define MINER_H

#include "Entity.h"
#include "../gameManager/Observer.h"
#include "../gameManager/Parameters.h"

#include <SFML/Graphics.hpp>
#include <SFML/Main.hpp>

#include <unordered_map>
#include <string>
#include <vector>
#include <utility>
#include <string>

/**@class Miner class
@brief Type of Entity meant to mine for Ore, which is the objective of a game */
class Miner : public Entity
{
    public:
        //constructor
        /** @brief constructor */
        Miner(int xPos=-1, int yPos=-1);
        // destructor
        /** @brief destructor */
        ~Miner();

        //inherited function
        void on_Notify(Component* subject, Event event);
        void _init();
        int stateValue();
        std::string getStateS();
        void check();
        void action();
        void answer_radar(std::shared_ptr<Entity> e);
        std::string tostring();

        //Class skills
        /** @brief looks for ore on the map and saves their positions in
        objectives_positions */
        void checkForOre();
        /** @brief */
        void addOreObjective(sf::Vector2i pos);
        /** @brief */
        sf::Vector2i getTopOre();
        /** @brief takes ore next to it (1 tile distance) */
        void mine();
        /** @brief permits the bag to get filled */
        void fillBag();
        /** @brief gives the base the collected ore (1 tile distance) */
        void depositOre();


    protected:

    private:
        //Base type definition
        typedef Entity super;

        //attributes
        std::vector<sf::Vector2i> objectives_positions; //positions of the ora objectives to collect
};

#endif // MINER_H
