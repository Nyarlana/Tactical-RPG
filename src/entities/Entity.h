#ifndef ENTITY_H
#define ENTITY_H

class Entity
{
    public:
        //constructor
        Entity(int max_LP, int xPos, int yPos, int speed);
        //destructor
        virtual ~Entity();

        //modifiers
        void takeDamage(int value); //lowers this.lp by value, then if lp<=0, the entity is considered dead and so calls die()
        void die();                 //dying action (including the destruction of the object)

        //actions
        virtual void action() = 0;
        virtual void moveOut() = 0;

    protected:

    private:
        int max_LP;                 //max life points of the Entity,
        int lp;                     //life points of the Entity,
        int xPos, yPos;             //position of the Entity
        int speed;                  //number of Tiles the Entity can go through in one move()
};

#endif // ENTITY_H
