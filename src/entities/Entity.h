/**@file Entity header*/
#ifndef ENTITY_H
#define ENTITY_H

#define ANIM_TIME 500
#define FRAME_TIME 17

#include "../gameManager/Component.h"
#include "../gameManager/Observer.h"
#include "../gameManager/Parameters.h"
#include "../UI/UI.h"

#include <SFML/Graphics.hpp>
#include <SFML/Main.hpp>

#include <math.h>
#include <iostream>
#include <memory>
#include <string>
#include <mutex>
#include <condition_variable>

/* @brief State enum */
enum State {
    SEARCH,
    OUTER,
    PROTECTION,
    HEAL,
    OFFENSIVE,
    EXPLORATION,
    MINER,
    GIVER,
    PICKER,
    END_GAME,
    RANDOM
};

static int entity_number = 0;

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
        virtual void on_Notify(Component* subject, Event event) = 0;
        virtual void _init() = 0;
        void _update();
        void _draw(sf::RenderWindow & window);

        //Getter
        sf::Vector2i getPos();
        /** @brief gets the distance to another Entity */
        int getDistanceTo(std::shared_ptr<Entity> e);
        int getDistanceTo(sf::Vector2i other_pos);
        sf::Vector2i getNextPos();
        int lacksLP();
        virtual int stateValue() = 0;
        virtual std::string getStateS() = 0;
        sf::Vector2i getTopTargetPos();
        void setTopTargetPos(sf::Vector2i pos);
        void setPath(std::vector<sf::Vector2i> new_path);
        /** @brief tells if the Entity is dead */
        bool isDead();
        int getID();

        //modifiers
        /** @brief groups all the checks an Entity is going to make before its action*/
        virtual void check() = 0;
        /** @brief Lowers this.lp by value, then if lp<=0, the entity is considered dead and so calls die()
        @param value amount of points lp is lowered*/
        void takeDamage(int value);
        void setPos(sf::Vector2i newPos);
        void setTopTarget(sf::Vector2i pos);
        void setState(State s);
        /** @brief dying action (including the destruction of the object) */
        void die();
        /** @brief adds e to either rov or al depending on isRov
        @param isRov tells if e is to add to rov, or to al
        @param e Entity to add
        */
        void add(bool isRov, std::shared_ptr<Entity> e);

        //actions
        /** @brief The Entity specific behavior*/
        virtual void action() = 0;
        /** @brief action to move for an Entity*/
        void move();
        void pause();
        virtual void answer_radar(std::shared_ptr<Entity> e) = 0;
        virtual std::string tostring() = 0;

    protected:
        //attributes
        int speed;                  //number of Tiles the Entity can go through in one move()
        int lp;                     //life points of the Entity
        State state;
        sf::Vector2i pos;           //position of the Entity
        sf::Texture texture;
        sf::Sprite  sprite;
        int target_distance;
        std::vector<sf::Vector2i> path;
        sf::Vector2i top_target;
        std::mutex* m;
        int last_pause;
        int delta_pause;
        std::shared_ptr<sf::Clock> clock;
        std::vector<std::shared_ptr<Entity>> rov;
        std::vector<std::shared_ptr<Entity>> al;
        UI_ProgressBar* pb;
        UI_TextBox* tb;
        int id;
        int max_LP;                 //max life points of the Entity,

    private:
        //Base type definition
        typedef Component super;

};

#endif // ENTITY_H
