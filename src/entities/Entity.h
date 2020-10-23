/**@file Entity header*/
#ifndef ENTITY_H
#define ENTITY_H

#include "../gameManager/Component.h"
#include "../gameManager/Observer.h"

#include <SFML/Graphics.hpp>
#include <SFML/Main.hpp>

#include <math.h>
#include <memory>

/* @brief State enum */
enum State {
    SEARCH,
    OUTER,
    PROTECTION,
    HEAL,
    OFFENSIVE,
    EXPLORATION,
    MINER,
    PICKER,
    END_GAME
};

/**@class Entity class
@brief Base Class to emulate Rovers and Aliens */
class Entity : public Component, public Subject
{
    public:
        //constructor
        /** @brief constructor */
        Entity(int max_LP, int xPos, int yPos, int speed);
        //destructor
        /** @brief destructor */
        ~Entity();

        //inherited functions
        virtual void _init() = 0;
        virtual void _update() = 0;
        virtual void _draw(sf::RenderWindow & window) = 0;

        //Getter
        /** @brief gets the distance to another Entity */
        sf::Vector2i getPos();
        int getDistanceTo(std::shared_ptr<Entity> e);
        /** @brief tells if the Entity is dead */
        bool isDead();

        //modifiers
        /** @brief Lowers this.lp by value, then if lp<=0, the entity is considered dead and so calls die()
        @param value amount of points lp is lowered*/
        void takeDamage(int value);
        /** @brief dying action (including the destruction of the object) */
        void die();

        //actions
        /** @brief The Entity general behavior*/
        virtual double operator() () = 0;
        /** @brief action to move for an Entity*/
        void moveTo(sf::Vector2i newPos);

    protected:
        int speed;                  //number of Tiles the Entity can go through in one move()
        int lp;                     //life points of the Entity,
        State state;

    private:
        //Base type definition
        typedef Component super;

        //attributes
        int max_LP;                 //max life points of the Entity,
        sf::Vector2i pos;           //position of the Entity
};

#endif // ENTITY_H
