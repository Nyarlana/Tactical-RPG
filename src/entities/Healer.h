#ifndef HEALER_H
#define HEALER_H

#include <Fighter.h>

class Healer : public Fighter
{
    public:
        //constructor
        Healer(int xPos, int yPos); //threatfullTargetCheckArea=0
        //destructor
        virtual ~Healer();

        //inherited functions
        void action();
        void attack();

        //Class skills
        void setNeed(std::shared_ptr<Entity> target, int needSet);   //sets heal need of a specific target, if the target isn't already is the target list, adds it to the list
        void heal(std::shared_ptr<Entity> target); //heals the target's life points by ?? points

    protected:

    private:
        void checkTargets();                //looks for targets in its areas and erases targets outside them
};

#endif // HEALER_H
