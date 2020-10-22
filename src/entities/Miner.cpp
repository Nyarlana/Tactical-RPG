#include "Miner.h"

using namespace std;

Miner::Miner(int xPos, int yPos) : Entity(4, xPos, yPos, 3)
{
    //ctor
}

Miner::~Miner()
{
    //dtor
}

//inherited function
void Miner::_init()
{

}

void Miner::_update()
{

}

void Miner::_draw(sf::RenderWindow & window)
{

}

double Miner::operator()()
{
    while (lp>0)
    {
        //super::checkTargets();
    }

    return 0.0;
}

//Class skills
/** @brief looks for ore on the map and saves their positions in
objectives_positions */
void Miner::checkForOre()
{
    //calls the GM to a list of Ore positions and add it to target
}

/** @brief takes ore next to it (1 tile distance) */
void Miner::mine()
{
    //calls the GM to check if there's at least one ore at 1 tile distance
    // then -> removes one ore around and sets bagFull to true
}

void Miner::depositOre()
{
    //calls the GM to check if the base is at 1 tile distance
    // then -> adds one ore to the base reserve and sets bagFull to false
}
