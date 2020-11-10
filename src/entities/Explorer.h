/**@file Explorer header*/
#ifndef Explorer_H
#define Explorer_H

#define MAX_SIZE_X 25
#define MAX_SIZE_Y 25

#include "Rover.h"

/**@class Explorer class
@brief Explorer type of Rover*/
class Explorer : public Rover
{
    public:
        /** @brief constructor */
        Explorer(int max_LP, int xPos, int yPos, int speed, int acuity);

        //inherited functions
        void on_Notify(Component* subject, Event event);
        virtual void action() = 0;

        //Class skills
        /* @brief
        */
        void computePositionToExplore();
        void completeMap();
        void setExplorerObjective(std::vector<sf::Vector2i> obj);
    protected:
        int[MAX_SIZE_X][MAX_SIZE_Y] map;

    private:
        //Base type definition
        typedef Rover super;
        int visual_acuity;
        std::vector<sf::Vector2i> explorer_objective;
};

#endif // Explorer_H
