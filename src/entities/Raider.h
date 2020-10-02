#ifndef RAIDER_H
#define RAIDER_H

#include <Fighter.h>


class Raider : public Fighter
{
    public:
        //constructor
        Raider(int xPos, int yPos);
        //destructor
        virtual ~Raider();

        //inherited functions
        void action();
        void attack();

        //Class skills
        void speedup();     //accelerates the Raider's speed
        void lowProfile();  //decreases the Raider's threat value by ?? points the Aliens see in this Raider

    protected:

    private:
};

#endif // RAIDER_H
