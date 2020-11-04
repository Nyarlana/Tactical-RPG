/**@file Protector header*/
#ifndef Protector_H
#define Protector_H

#include "Rover.h"

/**@class Protector class
@brief Protector type of Rover*/
class Protector : public Rover
{
    public:
        /** @brief constructor */
        Protector(int max_LP, int xPos, int yPos, int speed, int instinct);

        //inherited functions
        void on_Notify(const Component* subject, Event event);
        virtual double operator() () = 0;
        void die(); //notifies it's dead and launches a distress_call its position

        //class skills
        std::vector<std::shared_ptr<Entity>> findEntities();
        void identifyEntity(std::shared_ptr<Entity>);
        std::shared_ptr<Rover> getFirstToProtect();
        void distress_call(sf::Vector2i call_pos);

    protected:
        std::vector<std::shared_ptr<Rover>> underProtection;

    private:
        //Base type definition
        typedef Rover super;
        int protection_instinct;
};

#endif // Protector_H
