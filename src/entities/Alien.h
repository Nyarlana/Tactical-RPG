#ifndef ALIEN_H
#define ALIEN_H

#include <Fighter.h>

class Alien : public Fighter
{
    public:
        //constructor
        Alien(int xPos, int yPos, bool hasAggressiveBehavior);
        //destructor
        virtual ~Alien();

        //inherited functions
        void action();
        void moveOut();
        void die();                                                 //overrides Entity::die(), destructs itself after notifying its group of its death
        void attack();

    protected:

    private:
        bool hasAggressiveBehavior;         //constant, inherited through its Alien-type
};

#endif // ALIEN_H
