#ifndef ALIEN_H
#define ALIEN_H

#include <Fighter.h>
#include <unordered_map>


class Alien : public Fighter
{
    public:
        Alien(int lp, int xPos, int yPos, int speed, bool hasAggressiveBehavior, int targetCheckArea, int threatfullTargetCheckArea);
        void action();
        void die();                                                 //overrides Entity::die(), destructs itself after notifying its group of its death
        virtual ~Alien();

    protected:

    private:
        bool hasAggressiveBehavior;         //constant, inherited through its Alien-type
};

#endif // ALIEN_H
