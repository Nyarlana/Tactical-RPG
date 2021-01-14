/**@file Explorer header*/
#ifndef EXPLORER_H
#define EXPLORER_H

#include "Entity.h"
#include "Parameters.h"

/**@class Explorer class*/
class Explorer
{
    public:
        /** @brief constructor */
        Explorer(int acuity);

        //Class skills
        /** @brief looks for a position to reach on the map in order to complete
        the map in an optimized and coordinated way
        */
        void computePositionToExplore();
        /** @brief completes the shared map, telling which type of Tile the Tiles
        in acuity radius are*/
        void completeMap();
        /** @brief helps the other Explorers to know if a position is already
        targeted as an exploration target to avoid for several Explorer to try and
        explore the same position*/
        void setExplorerObjective(std::vector<sf::Vector2i> obj);

    protected:
        static int[X_SIZE][Y_SIZE] map;

    private:
        int visual_acuity;
        std::vector<sf::Vector2i> taken_objectives;
        std::vector<sf::Vector2i> exploring_path;
};

#endif // EXPLORER_H
