#ifndef RAIDER_H
#define RAIDER_H

#include <Fighter.h>


class Raider : public Fighter
{
    public:
        Raider(int xPos, int yPos);
        void action();
        void speedup();     //accelerates the Raider's speed
        void lowProfile();  //decreases the Raider's threat value by ?? points the Aliens see in this Raider
        void attack();
        virtual ~Raider();

    protected:

    private:
};

#endif // RAIDER_H
