#include "RoverBase.h"

#include <string>
#include <thread>
#include <fstream>
#include <iostream>
#include <stdexcept>      // std::invalid_argument

using namespace std;
/** @brief constructor */
RoverBase::RoverBase(int _x_pos, int _y_pos, int _objective, string _rovers) : Entity(20, _x_pos, _y_pos, 4), objective(_objective)
{
    string type;

    while (!_rovers.empty())
    {
        switch (_rovers.back())
        {
            case 'h':
            {
                type = "Healer";
                rovers.push_back(make_shared<Healer>());
                break;
            }
            case 'm':
            {
                type = "Miner";
                rovers.push_back(make_shared<Miner>());
                break;
            }
            case 'r':
            {
                type = "Raider";
                rovers.push_back(make_shared<Raider>());
                break;
            }
            case 't':
            {
                type = "Tank";
                rovers.push_back(make_shared<Tank>());
                break;
            }
        }

        std::cout << "A "<<type<<" was created"<< '\n';
        _rovers.pop_back();
    }
}

//inherited functions
void RoverBase::on_Notify(Component* subject, Event event)
{
}

void RoverBase::add_Observer(std::shared_ptr<Observer> obs)
{
    Subject::add_Observer(obs);

    for(int i=0; i<rovers.size(); i++)
    {
        rovers[i]->add_Observer(obs);
    }
}

void RoverBase::_init()
{
    for(int i=0; i<rovers.size(); i++)
    {
        notify(rovers[i].get(), GM_ADD_THREAD);
        // rovers[i]->add_Observer(Observer::shared_from_this());
        rovers[i]->_init();
    }

    Entity::state = PICKER;

    // if(!texture.loadFromFile("data/entities/rover_base.png"))
    // {
    //   if(!texture.loadFromFile("../data/entities/rover_base.png"))
    //   {
    //     std::cout << "erreur" << '\n';
    //   }
    // }
    //
    // sprite.setTexture(texture);
    // sprite.setTextureRect(sf::IntRect(0,0,32,32));
}

int RoverBase::stateValue()
{
    return (Entity::state==PICKER || Entity::state==END_GAME)?1:-1;
}

void RoverBase::_update()
{
    Entity::_update();

    for(int i=0; i<rovers.size(); i++)
        rovers[i]->_update();
}

void RoverBase::_draw(sf::RenderWindow & window)
{
    Entity::_draw(window);

    for(int i=0; i<rovers.size(); i++)
        rovers[i]->_draw(window);
}

void RoverBase::action()
{
    switch(state)
    {
        case PICKER:
        {
            break;
        }
        case END_GAME:
        {
            break;
        }
        default:
        {
            Entity::state = PICKER;
        }
    }
}

void RoverBase::moveTo(sf::Vector2i newPos) //doesn't move at all
{

}

void RoverBase::missionComplete()
{
    int timeOut=3;

    //call to all Rovers to come back with timeOut (distance from farthest rover)

    while((timeOut--)>0)
        pause();

    //notify the GameManager that the game is over
}

void RoverBase::die()
{
    for(int i=0; i<rovers.size(); i++)
        rovers[i]->die();
    std::cout << "This RoverBase just died" << '\n';
}

RoverBase RoverBase::launchMission(string mission)
{
    string line;

    int x_pos = -100;
    int y_pos = -100;
    int obj = -100;
    string rovers = "";

    mission = "data/" + mission + ".msn";
    ifstream mission_file (mission);
    if (mission_file.is_open())
    {
        while (getline (mission_file,line))
        {
            int separator;

            string data_type = line.substr(0,3);

            if(data_type.compare("pos")==0)
            {
                line = line.substr(4);

                try
                {
                    int separator = line.find_first_of(",");

                    x_pos = stoi(line.substr(0,separator));
                    y_pos = stoi(line.substr(separator+1));
            	}
            	catch (std::invalid_argument const &e)
            	{
            		std::cout << "Bad input: std::invalid_argument thrown" << '\n';
            	}
            	catch (std::out_of_range const &e)
            	{
            		std::cout << "Integer overflow: std::out_of_range thrown" << '\n';
            	}
            }
            else if(data_type.compare("obj")==0)
            {
                try
                {
                    obj = stoi(line.substr(4));
            	}
            	catch (std::invalid_argument const &e)
            	{
            		std::cout << "Bad input: std::invalid_argument thrown" << '\n';
            	}
            	catch (std::out_of_range const &e)
            	{
            		std::cout << "Integer overflow: std::out_of_range thrown" << '\n';
            	}
            }
            else if(data_type.compare("rov")==0)
            {
                rovers += line.back();
            }
        }

        cout<<"pos : " << x_pos << "," << y_pos <<endl;
        cout<<"obj : " << obj <<endl;
        cout<<"rov : " << rovers <<endl;

        cout<<"test open : "<< (mission_file.is_open()?"yes":"no") <<endl;

        mission_file.close();
    }

    return RoverBase(x_pos, y_pos, obj, rovers);
}

//Rovers management

void RoverBase::getOneOre()
{
    ore_amount++;

    if(ore_amount==objective)
        missionComplete();
}

void RoverBase::putRover(int rover_number, int x, int y)
{

}

/*void getRover(Rover r)
{

}*/
