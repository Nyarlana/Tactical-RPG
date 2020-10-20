#include "RoverBase.h"

#include <vector>
#include <string>
#include <memory>

using namespace std;
/** @brief constructor */
RoverBase::RoverBase(int _x_pos, int _y_pos, int _objective, string _rovers) : x_pos(_x_pos), y_pos(_y_pos), objective(_objective)
{
    while (!_rovers.empty())
    {
        switch (_rovers.back())
        {
            case 'h':
                rovers.push_back(std::make_shared<Healer>(-1,-1));
                break;
            case 'm':
                rovers.push_back(std::make_shared<Miner>(-1,-1));
                break;
            case 'r':
                rovers.push_back(std::make_shared<Raider>(-1,-1));
                break;
            case 't':
                rovers.push_back(std::make_shared<Tank>(-1,-1));
        }

        _rovers.pop_back();
    }
}

//inherited functions
void _init()
{
    for(int i=0; i<rovers.size(); i++)
        // on lance les theads rover : rovers[i]->action();

    //on lance ce thread
}

void _update()
{

}

void _draw(sf::RenderWindow & window)
{

}

void action()
{

}

void moveOut() //doesn't move at all
{

}

void missionComplete()
{
    //call to all Rovers to come back with timeOut
    //until notifying the GameManager that the game is over
}


void die()
{
    //kills all Rovers and notifies the GameManager that the game
    //is over
}

static RoverBase launchMission(string mission)
{
    string line, data_type;
    int separator;

    int x_pos, y_pos, objective;
    string rovers = "";

    ifstream mission_file ("../../data/" + mission + ".msn");

    if (mission_file.is_open())
    {
        while (getline (mission_file,line))
        {
            getline (mission_file,line);
            string data_type = line.substr(0,3);

            if(data_type.compare("pos"))
            {
                line = line.substr(4);

                separator = line.find_first_of(":");

                x_pos = stoi(line.substr(0,separator));
                y_pos = stoi(line.substr(separator+1));
            }
            else if(data_type.compare("obj"))
            {
                objective = stoi(line.substr(4));
            }
            else if(data_type.compare("rov"))
            {
                rovers.append(line.back());
            }
        }

        mission_file.close();

        return new RoverBase(x_pos, y_pos, objective, rovers);
    }

    return NULL;
}

//Rovers management
void getOneOre()
{

}

void putRover(int rover_number, int x, int y)
{

}

void getRover(Rover r)
{

}
