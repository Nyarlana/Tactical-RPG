#ifndef MINER_H
#define MINER_H

#include <Entity.h>
#include <unordered_map>
#include <string>
#include <vector>
#include <utility>

class Miner : public Entity
{
    public:
        //constructor
        Miner(int xPos, int yPos);
        //destructor
        virtual ~Miner();

        //inherited function
        void action();

        //Class skills
        void checkForOre(); //looks for ore on the map and saves their positions in objectives_positions
        void mine();        //takes ore next to it (at 1 tile distance ?)
        bool canAddToBag();

    protected:

    private:
        bool bagFull;                                         //has an ore
        std::vector<std::pair<int,int>> objectives_positions; //positions of the ora objectives to collect
};

#endif // MINER_H
