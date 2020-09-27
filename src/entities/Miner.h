#ifndef MINER_H
#define MINER_H

#include <Entity.h>

class Miner :: public Entity
{
    public:
        Miner(int max_LP, int xPos, int yPos, int speed, int bagSize);
        void action();
        void checkForOre(); //looks for ore on the map and saves their positions in objectives_positions
        void mine();        //takes ore next to it (maybe all around at 1 tile distance ?)
        //void bagSizeUpdate(); => increase size after depositing ore at the base ?
        bool canAddToBag(int ore_weight);
        virtual ~Miner();

    protected:

    private:
        int bagSize;                                //maximum weight the Miner's bag can contain
        unordered_map<string, int> bag;             //bag content
        vector<pair(int,int)> objectives_positions; //positions of the ora objectives to collect
};

#endif // MINER_H
