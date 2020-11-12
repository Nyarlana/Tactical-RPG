/**@file AlienGroup header*/
#ifndef ALIEN_GROUP_H
#define ALIEN_GROUP_H

#include "Alien.h"

#include "../gameManager/Component.h"
#include "../gameManager/Observer.h"

#include <SFML/Graphics.hpp>
#include <SFML/Main.hpp>

#include <vector>

/**@class AlienGroup class
@brief Group of Aliens*/
class AlienGroup : public Component, public Observer, public Subject
{
    public:
        /** @brief constructor */
        AlienGroup(int alien_number=1, int average_alien_stats=4);

        //inherited functions
        void on_Notify(Component* subject, Event event);
        void add_Observer(std::shared_ptr<Observer> obs);
        void _init();
        void _update();
        void _draw(sf::RenderWindow & window);
        void action();
        void die();
    private:
        std::vector<std::shared_ptr<Alien>> aliens;
        int alien_number;
};

#endif // ALIEN_GROUP_H
