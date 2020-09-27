#ifndef HEALER_H
#define HEALER_H

#include <Fighter.h>


class Healer : public Fighter
{
    public:
        Healer(int lp, int xPos, int yPos, int speed, int targetCheckArea); //threatfullTargetCheckArea=0
        void action();
        void setNeed(Entity* target, int needSet);   //sets heal need of a specific target, if the target isn't already is the target list, adds it to the list
        void heal(Entity *target); //heals the target's life points by ?? points
        virtual ~Healer();

    protected:

    private:
        void checkTargets();                //looks for targets in its areas and erases targets outside them
};

#endif // HEALER_H
