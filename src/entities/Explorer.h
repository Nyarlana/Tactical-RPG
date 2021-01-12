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
        /* @brief
        */
        void computePositionToExplore();
        void completeMap();
        void setExplorerObjective(std::vector<sf::Vector2i> obj);

    protected:
        static int[X_SIZE][Y_SIZE] map;

    private:
        int visual_acuity;
        std::vector<sf::Vector2i> taken_objectives;
        std::vector<sf::Vector2i> exploring_path;
};

#endif // EXPLORER_H
