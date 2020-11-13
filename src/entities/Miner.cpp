#include "Miner.h"

using namespace std;

Miner::Miner(int xPos, int yPos) : Entity(4, xPos, yPos, 3), bagFull(false)
{
    //ctor
}

Miner::~Miner()
{
    //dtor
}

//inherited function
void Miner::on_Notify(Component* subject, Event event)
{

}

void Miner::_init()
{
    super::state = OUTER;

    if(!texture.loadFromFile("data/entities/miner.png"))
    {
      if(!texture.loadFromFile("../data/entities/miner.png"))
      {
        std::cout << "erreur" << '\n';
      }
    }

    sprite.setTexture(texture);
    sprite.setTextureRect(sf::IntRect(0,0,32,32));
}

int Miner::stateValue()
{
    int value;

    switch(state)
    {
        case OUTER:
        {
            value = 0;
            break;
        }
        case EXPLORATION:
        {
            value = 1;
            break;
        }
        case MINER:
        {
            value = 2;
            break;
        }
        case END_GAME:
        {
            value = 3;
            break;
        }
        default:
        {
            value = -1;
        }
    }

    return value;
}

void Miner::action()
{
    if(state!=OUTER && state!=END_GAME)
        checkForOre();

    switch(state)
    {
        case OUTER:
        {
            notify(this, E_OUT_REQ);
            while (pos.x==-1) {
                pause();
                std::cout << "miner is waiting..." << '\n';
            }
            state=SEARCH;
            break;
        }
        case EXPLORATION:
        {
            if(path.empty())
                notify(this, E_GET_RANDOM_PATH);
            moveTo(path.back());
            path.pop_back();
            break;
        }
        case MINER:
        {
            std::cout << "miner mode" << '\n';
            if(!bagFull)
            {
                std::cout << "bag not full" << '\n';
                if(path.empty() || (path.back().x==pos.x && path.back().y==pos.y))
                {
                    path.clear();
                    mine();
                }
                else
                {
                    std::cout << "next pos : " <<path.back().x<<","<<path.back().y<< '\n';
                    moveTo(path.back());
                    path.pop_back();
                }
            }
            else
            {
                std::cout << "bag full" << '\n';
                notify(this,E_REQ_PATH_BASE);
                //if(path.empty())
                    depositOre();
                /*else
                {
                    moveTo(path.back());
                    path.pop_back();
                }*/
            }

            break;
        }
        case END_GAME:
        {
            std::cout << "mission complete : back to rover base" << '\n';
            notify(this,E_REQ_PATH_BASE);
            break;
        }
        default:
        {
            state = EXPLORATION;
        }
    }
}

//Class skills
/** @brief looks for ore on the map and saves their positions in
objectives_positions */
void Miner::checkForOre()
{
    notify(this,E_EXP_ORE_CHECK);

    if(bagFull)
    {
        std::cout << "--------------------------- back to RoverBase --------------------------" << '\n';
    }
    if(!objectives_positions.empty())
    {
        std::cout << "-----------------------------------------------------" << '\n';
        state=MINER;
        notify(this, E_GET_PATH_ORE);
    }
}

void Miner::addOreObjective(sf::Vector2i pos)
{
    bool is_already_obj = false;

    for(int i=0; i<objectives_positions.size(); i++)
        if(objectives_positions[i].x == pos.x && objectives_positions[i].y == pos.y)
            is_already_obj = true;

    if(!is_already_obj)
        objectives_positions.push_back(pos);
}

sf::Vector2i Miner::getTopOre()
{
    return objectives_positions.back();
}

/** @brief takes ore next to it (1 tile distance) */
void Miner::mine()
{
    notify(this,E_MINE_OCCURS);
    pause();
    bagFull = true;
    objectives_positions.pop_back();
}

void Miner::depositOre()
{
    notify(this,E_DEP_ORE);
    bagFull = false;

    if(objectives_positions.empty())
        state = EXPLORATION;
}
