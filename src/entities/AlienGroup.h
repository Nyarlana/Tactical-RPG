/**@file AlienGroup header*/
#ifndef ALIEN_GROUP_H
#define ALIEN_GROUP_H

#include "entities.h"

#include "../gameManager/Component.h"
#include "../gameManager/Observer.h"

#include <SFML/Graphics.hpp>
#include <SFML/Main.hpp>

#include <vector>
#include <thread>

/**@class AlienGroup class
@brief Group of Aliens*/
class AlienGroup : public Component, public Observer, public Subject
{
    public:
        /** @brief constructor */
        AlienGroup(int alien_number, int average_alien_stats);

        //inherited functions
        void on_Notify(const Component* subject, Event event);
        void _init();
        void _update();
        void _draw(sf::RenderWindow & window);
        void action();
        void die();
    protected:
    private:
        std::vector<std::thread> threads;
        std::vector<std::shared_ptr<Alien>> aliens;
        int alien_number;
};

#endif // ALIEN_GROUP_H
