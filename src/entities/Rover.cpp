#include "Rover.h"

using namespace std;

Rover::Rover(int max_LP, int xPos, int yPos, int speed) : Entity(max_LP, xPos, yPos, speed)
{

}

void Rover::die()
{
    super::notify(ref(this), EVENT_TEST);
    super::die();
}
