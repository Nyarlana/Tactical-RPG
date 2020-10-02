#ifndef TANK_H
#define TANK_H

#include <Fighter.h>


class Tank : public Fighter
{
    public:
        Tank(int xPos, int yPos);
        void action();
        void tease();               //increases by ?? points the threat Aliens around see in this Tank
        void taunt(std::shared_ptr<Alien> alien);   //multiplies by ?? the threat the selected Alien see in this Tank
        void attack();
        virtual ~Tank();

    protected:

    private:
};

#endif // TANK_H
