/**@file Miner header*/
#ifndef MINER_H
#define MINER_H

#include "Entity.h"
#include "../gameManager/Observer.h"

#include <SFML/Graphics.hpp>
#include <SFML/Main.hpp>

#include <unordered_map>
#include <string>
#include <vector>
#include <utility>

/**@class Miner class
@brief Type of Entity meant to mine for Ore, which is the objective of a game */
class Miner : public Entity
{
    public:
        //constructor
        /** @brief constructor */
        Miner(int xPos, int yPos);
        // destructor
        /** @brief destructor */
        ~Miner();

        //inherited function
        void on_Notify(const Component* subject, Event event);
        void _init();
        int stateValue();
        double operator() ();

        //Class skills
        /** @brief looks for ore on the map and saves their positions in
        objectives_positions */
        void checkForOre();
        /** @brief takes ore next to it (1 tile distance) */
        void mine();
        /** @brief gives the base the collected ore (1 tile distance) */
        void depositOre();

    protected:

    private:
        //Base type definition
        typedef Entity super;

        //attributes
        bool bagFull;                                         //has an ore
        std::vector<sf::Vector2i> objectives_positions; //positions of the ora objectives to collect
};

#endif // MINER_H
