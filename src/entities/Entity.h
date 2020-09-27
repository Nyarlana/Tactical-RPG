#ifndef ENTITY_H
#define ENTITY_H

class Entity
{
    public:
        Entity(int max_LP, int xPos, int yPos, int speed);
        virtual ~Entity();
        void takeDamage(int value); //lowers this.lp by value, then if lp<=0, the entity is considered dead and so calls die()
        void die();                 //dying action (including the destruction of the object)
        virtual void action();
        virtual void moveOut();

    protected:

    private:
        int max_LP;                 //max life points of the Entity,
        int lp;                     //life points of the Entity,
        int xPos, yPos;             //position of the Entity
        int speed;                  //number of Tiles the Entity can go through in one move()
};

#endif // ENTITY_H
