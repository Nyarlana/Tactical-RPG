#include "../entities/Miner.h"
#include "../entities/Alien.h"
#include "../entities/Tank.h"
#include "../entities/Raider.h"
#include "../entities/Healer.h"
#include "../entities/RoverBase.h"

#include <memory>
#include <thread>
#include <iostream>

using namespace std;

int main()
{
    if(0)
    {
        auto a = std::make_shared<Alien>(6, 2, 2, 2, 3, 5, true);
        auto r = std::make_shared<Raider>(1,2);
        auto t = std::make_shared<Tank>(2,1);
        auto h = std::make_shared<Healer>(3,3);
        auto m = std::make_shared<Miner>(1,1);

        a->attack(m);
        h->heal(m);
        a->attack(m);
        t->attack(a);
        r->attack(a);
    }
    else if(0)
    {
        Alien a(6, 2, 2, 2, 3, 5, true);
        thread t_a (a);
        auto ptr_a = std::make_shared<Alien>(a);

        auto r = std::make_shared<Raider>(1,2);
        auto t = std::make_shared<Tank>(2,1);
        auto h = std::make_shared<Healer>(3,3);
        auto m = std::make_shared<Miner>(1,1);


        ptr_a->attack(m);
        h->heal(m);
        ptr_a->attack(m);
        t->attack(ptr_a);
        r->attack(ptr_a);

        t_a.detach();

        std::cout << "test terminé" << std::endl;
    }
    else if(1)
    {
        RoverBase rb(RoverBase::launchMission("mission"));
        rb.die();
    }

    return 0;
}
