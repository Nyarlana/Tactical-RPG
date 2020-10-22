#include "RoverBase.h"

#include "Healer.h"
#include "Miner.h"
#include "Raider.h"
#include "Tank.h"

#include <vector>
#include <string>
#include <memory>
#include <thread>
#include <fstream>
#include <iostream>
#include <stdexcept>      // std::invalid_argument

using namespace std;
/** @brief constructor */
RoverBase::RoverBase(int _x_pos, int _y_pos, int _objective, string _rovers) : Entity(20, _x_pos, _y_pos, 0), objective(_objective)
{
    while (!_rovers.empty())
    {
        switch (_rovers.back())
        {
            case 'h':
            {
                Healer h(-1,-1);
                rovers.push_back(std::make_shared<Healer>(h));
                threads.push_back(thread(h));
                break;
            }
            case 'm':
            {
                Miner m(-1,-1);
                rovers.push_back(std::make_shared<Miner>(m));
                threads.push_back(thread(m));
                break;
            }
            case 'r':
            {
                Raider r(-1,-1);
                rovers.push_back(std::make_shared<Raider>(r));
                threads.push_back(thread(r));
                break;
            }
            case 't':
            {
                Tank t(-1,-1);
                rovers.push_back(std::make_shared<Tank>(t));
                threads.push_back(thread(t));
            }
        }

        _rovers.pop_back();
    }
}

//inherited functions
void RoverBase::_init()
{
    for(int i=0; i<threads.size(); i++)
        threads[i].join();

    //on lance ce thread
}

void RoverBase::_update()
{

}

void RoverBase::_draw(sf::RenderWindow & window)
{

}

double RoverBase::operator()()
{
    while (lp>0)
    {
        //super::checkTargets();
    }

    return 0.0;
}

void RoverBase::moveTo(sf::Vector2i newPos) //doesn't move at all
{

}

void RoverBase::missionComplete()
{
    //call to all Rovers to come back with timeOut
    //until notifying the GameManager that the game is over
}


void RoverBase::die()
{
    for(int i=0; i<threads.size(); i++)
        threads[i].detach();
    std::cout << "This RoverBase just died" << '\n';
}

RoverBase RoverBase::launchMission(string mission)
{
    string line;

    int x_pos = -100;
    int y_pos = -100;
    int obj = -100;
    string rovers = "";

    ifstream mission_file ("data/" + mission + ".msn");
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

        mission_file.close();

        cout<<"test open : "<< (mission_file.is_open()?"yes":"no") <<endl;
    }

    return RoverBase(x_pos, y_pos, obj, rovers);
}

//Rovers management
void RoverBase::setGameManager(shared_ptr<GameManager> gm)
{
    add_Observer(gm);

    for(int i; i<rovers.size(); i++)
        rovers[i]->add_Observer(gm);
}

void RoverBase::getOneOre()
{

}

void RoverBase::putRover(int rover_number, int x, int y)
{

}

/*void getRover(Rover r)
{

}*/
