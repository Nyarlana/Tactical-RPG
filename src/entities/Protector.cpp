#include "Protector.h"

using namespace std;

Protector::Protector(int max_LP, int xPos, int yPos, int speed, int instinct) : Rover(max_LP, xPos, yPos, speed), protection_instinct(instinct)
{

}

//inherited functions
void Protector::on_Notify(const Component* subject, Event event)
{
    if(event==E_DISCALL)
        distress_call(((Entity*) subject)->getPos());
}

void Protector::die()
{
    if(underProtection.size()>0)
        notify(ref(this), E_DISCALL);
    super::die();
} //notifies it's dead and launches a distress_call its position

//class skills
void Protector::lookForEntities()
{
    notify(ref(this), E_REQ_LOOK_FOR_ENTITIES);
}

void Protector::identifyEntity(std::shared_ptr<Entity> e)
{
    if(is_base_of<Rover, e.get()>::value)
        underProtection.push_back(g);
}

std::shared_ptr<Rover> Protector::getFirstToProtect()
{
    //tri des underProtection en fonction de leurs pv restants puis
    //de leur distance à getPos()
    return null_ptr;
}

void Protector::distress_call(sf::Vector2i call_pos)
{
    if(distress_pos==null || getDistanceTo(distress_pos)>getDistanceTo(call_pos))
        distress_pos = call_pos;
}
