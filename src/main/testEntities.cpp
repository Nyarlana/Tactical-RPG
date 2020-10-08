#include "../entities/Miner.h"

int main() {
  Miner * m = new Miner(1,1);
  m->takeDamage(4);
  return 0;
}
