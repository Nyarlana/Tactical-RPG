/**@file AlienGroup header*/
#ifndef ALIEN_GROUP_H
#define ALIEN_GROUP_H

#include "Alien.h"

#include "../gameManager/Component.h"
#include "../gameManager/Observer.h"

#include <SFML/Graphics.hpp>
#include <SFML/Main.hpp>

#include <vector>

static int alienGroupNumber = 0;

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
        void answer_radar(std::shared_ptr<Entity> e);

        //class functions
        /** @brief Gives this number's group
        @return the group number
        */
        int getGroup();

        /** @brief Modifies pos
        @parameter _pos new value of pos
        */
        void setPos(sf::Vector2i _pos);
    private:
        int group_number;
        std::vector<std::shared_ptr<Alien>> aliens;
        int alien_number;
        sf::Vector2i pos;
};

#endif // ALIEN_GROUP_H
