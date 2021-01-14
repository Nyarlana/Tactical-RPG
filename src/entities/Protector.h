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
        /** @brief look for Entities to protect or attack within instinct radius */
        std::vector<std::shared_ptr<Entity>> findEntities();
        /** @brief verifies whether entity is an enemy or rover to protect */
        void identifyEntity(std::shared_ptr<Entity> entity);
        /** @brief gives the most optimal rover to protect */
        std::shared_ptr<Entity> getFirstToProtect();
        /** @brief receives a distress call on call_pos as a notification there's
        a loss on the rovers' side around that position */
        void distress_call(sf::Vector2i call_pos);

    protected:
        std::vector<std::shared_ptr<Rover>> underProtection;

    private:
        int protection_instinct;
};

#endif // PROTECTOR_H
