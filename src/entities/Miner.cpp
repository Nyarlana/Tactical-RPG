#include "Miner.h"

using namespace std;

Miner::Miner(int xPos, int yPos) : Entity(4, xPos, yPos, 3)
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
        case GIVER:
        {
            value = 3;
            break;
        }
        case END_GAME:
        {
            value = 4;
            break;
        }
        default:
        {
            value = -1;
        }
    }

    return value;
}

std::string Miner::getStateS()
{
    std::string the_string;

    switch (Entity::state)
    {
        case OUTER:
            return "OUTER";
        case EXPLORATION:
            return "SEARCH";
        case MINER:
            return "PROTECTION";
        case GIVER:
            return "GIVER";
        case END_GAME:
            return "END_GAME";
        default:
            return "ERROR";
    }

    return the_string;
}

void Miner::check()
{
    if(state!=OUTER && state!=END_GAME)
        checkForOre();
}

void Miner::action()
{
    switch(state)
    {
        case OUTER:
        {
            notify(this, E_OUT_REQ);
            while (pos.x==-1) {
                pause();
                if(TRACE_EXEC && MINER_TRACE)
                    std::cout << "miner is waiting..." << '\n';
            }
            state=EXPLORATION;
            break;
        }
        case EXPLORATION:
        {
            path.clear();
            if(TRACE_EXEC && MINER_TRACE)
                std::cout << "miner exploring...\n";

            notify(this, E_GET_RANDOM_PATH);

            move();
            break;
        }
        case MINER:
        {
            if(path.empty())
            {
                if(TRACE_EXEC && MINER_TRACE)
                    std::cout << "miner mining..." << '\n';

                mine();
            }
            else
            {
                if(TRACE_EXEC && MINER_TRACE)
                    std::cout << "approaching mining target..." << '\n';

                move();
            }

            break;
        }
        case GIVER:
        {
            if(TRACE_EXEC && MINER_TRACE)
                std::cout << "miner giving... " << path.size() << '\n';

            if(path.empty())
            {
                depositOre();
            }
            else
            {
                std::cout << "pos actuelle : " << pos.x << "," << pos.y << '\n';
                std::cout << "next pos     : " << path.back().x << "," << path.back().y << '\n';
                move();
            }

            break;
        }
        case END_GAME:
        {
            if(TRACE_EXEC && MINER_TRACE)
                std::cout << "mission complete : back to rover base" << '\n';
            if(path.size() >= 2)
            {
                move();
            }
            else
                std::cout << "arrived at roverbase" << '\n';
            break;
        }
        default:
        {
            state = EXPLORATION;
        }
    }
}

void Miner::answer_radar(std::shared_ptr<Entity> e)
{
    if(!isDead())
    {
        shared_ptr<Entity> me = std::dynamic_pointer_cast<Entity>(Observer::shared_from_this());
        e->add(true,me);
    }
}

//Class skills
/** @brief looks for ore on the map and saves their positions in
objectives_positions */
void Miner::checkForOre()
{
    notify(this,E_EXP_ORE_CHECK);

    if(!objectives_positions.empty())
    {
        if(TRACE_EXEC && MINER_TRACE)
            std::cout << "-----------------------------------------------------" << '\n';
        state=MINER;

        if(getDistanceTo(objectives_positions.back())>=2)
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
    pause();
    notify(this,E_MINE_OCCURS);

    objectives_positions.pop_back();

    if(state == GIVER)
    {
        path.clear();
        notify(this, E_REQ_PATH_BASE);
        path.pop_back();
    }
}

/** @brief permits the bag to get filled */
void Miner::fillBag()
{
    state = GIVER;
}

void Miner::depositOre()
{
    notify(this,E_DEP_ORE);
    state = MINER;

    if(objectives_positions.empty())
        state = EXPLORATION;
}

std::string Miner::tostring()
{
    return "miner";
}
