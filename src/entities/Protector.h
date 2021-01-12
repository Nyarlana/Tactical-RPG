/**@file Protector header*/
#ifndef PROTECTOR_H
#define PROTECTOR_H

#include "Entity.h"
#include "Parameters.h"

/**@class Protector class*/
class Protector
{
    public:
        /** @brief constructor */
        Protector(int instinct);

        void die(); //notifies it's dead and launches a distress_call its position

        //class skills
        std::vector<std::shared_ptr<Entity>> findEntities();
        void identifyEntity(std::shared_ptr<Entity>);
        std::shared_ptr<Entity> getFirstToProtect();
        void distress_call(sf::Vector2i call_pos);

    protected:
        std::vector<std::shared_ptr<Rover>> underProtection;

    private:
        int protection_instinct;
};

#endif // PROTECTOR_H
