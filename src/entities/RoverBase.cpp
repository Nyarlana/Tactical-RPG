#include "RoverBase.h"

#include <vector>
#include <string>

using namespace std;
/** @brief constructor */
RoverBase::RoverBase()
{

}

//inherited functions
void _init()
{

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
    vector<Entity> v;

    ifstream mission_file (mission);

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
                switch (line.back()) {
                    case 'm':
                    {
                        v.push_back(new Miner(-1,-1));
                    }
                    case 't':
                    {
                        v.push_back(new Tank(-1,-1));
                    }
                    case 'r':
                    {
                        v.push_back(new Raider(-1,-1));
                    }
                    case 'h':
                    {
                        v.push_back(new Healer(-1,-1));
                    }
                }
            }
        }

        mission_file.close();

        return new RoverBase(x_pos, y_pos, objective, v);
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
