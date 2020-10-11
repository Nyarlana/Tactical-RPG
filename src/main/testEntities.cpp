#include "../entities/Miner.h"
#include "../entities/Alien.h"
#include "../entities/Tank.h"
#include "../entities/Raider.h"
#include "../entities/Healer.h"

#include <memory>

using namespace std;

int main()
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

    return 0;
}
