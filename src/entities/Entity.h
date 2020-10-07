/**@file Entity header*/
#ifndef ENTITY_H
#define ENTITY_H

/**@class Entity class
@brief Base Class to emulate Rovers and Aliens */
class Entity
{
    public:
        //constructor
        /** @brief constructor */
        Entity(int max_LP, int xPos, int yPos, int speed);
        /** @brief destructor */
        virtual ~Entity();

        //modifiers
        /** @brief Lowers this.lp by value, then if lp<=0, the entity is considered dead and so calls die()
        @param value amount of points lp is lowered*/
        void takeDamage(int value);
        /** @brief dying action (including the destruction of the object) */
        void die();

        //actions
        /** @brief The Entity general behavior*/
        virtual void action() = 0;
        /** @brief action to move for an Entity*/
        virtual void moveOut() = 0;

    protected:

    private:
        int max_LP;                 //max life points of the Entity,
        int lp;                     //life points of the Entity,
        int xPos, yPos;             //position of the Entity
        int speed;                  //number of Tiles the Entity can go through in one move()
};

#endif // ENTITY_H
