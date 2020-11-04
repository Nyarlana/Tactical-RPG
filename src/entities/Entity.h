/**@file Entity header*/
#ifndef ENTITY_H
#define ENTITY_H

#define ANIM_TIME 1000
#define FRAME_TIME 17

#include "../gameManager/Component.h"
#include "../gameManager/Observer.h"

#include <SFML/Graphics.hpp>
#include <SFML/Main.hpp>

#include <math.h>
#include <memory>
#include <thread>

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
class Entity : public Component, public Observer, public Subject
{
    public:
        //constructor
        /** @brief constructor */
        Entity(int max_LP, int xPos, int yPos, int speed);
        //destructor
        /** @brief destructor */
        ~Entity();

        //inherited functions
        virtual void on_Notify(const Component* subject, Event event) = 0;
        virtual void _init() = 0;
        void _update();
        void _draw(sf::RenderWindow & window);

        //Getter
        /** @brief gets the distance to another Entity */
        sf::Vector2i getPos();
        int getDistanceTo(std::shared_ptr<Entity> e);
        virtual int stateValue() = 0;
        void setTopTargetPos(sf::Vector2i pos);
        void setPath(std::vector<sf::Vector2i> new_path);
        /** @brief tells if the Entity is dead */
        bool isDead();

        //modifiers
        /** @brief Lowers this.lp by value, then if lp<=0, the entity is considered dead and so calls die()
        @param value amount of points lp is lowered*/
        void takeDamage(int value);
        void setPos(sf::Vector2i newPos);
        /** @brief dying action (including the destruction of the object) */
        void die();

        //actions
        /** @brief The Entity general behavior*/
        double operator() ();
        /** @brief The Entity specific behavior*/
        virtual void action() = 0;
        /** @brief action to move for an Entity*/
        void moveTo(sf::Vector2i newPos);
        void pause();

    protected:
        int speed;                  //number of Tiles the Entity can go through in one move()
        int lp;                     //life points of the Entity
        State state;
        sf::Vector2i pos;           //position of the Entity
        sf::Texture texture;
        sf::Sprite  sprite;
        int target_distance;
        std::vector<sf::Vector2i> path;
        sf::Vector2i top_target;
        int last_pause;
        int delta_pause;

    private:
        //Base type definition
        typedef Component super;

        //attributes
        int max_LP;                 //max life points of the Entity,
};

#endif // ENTITY_H
