#include "Explorer.h"

using namespace std;

Explorer::Explorer(int max_LP, int xPos, int yPos, int speed, int acuity) : Rover(max_LP, xPos, yPos, speed), visual_acuity(acuity)
{
    for(int x=0; x<MAX_SIZE_X; x++)
        for(int y=0; y<MAX_SIZE_Y; y++)
            map[x][y]=-1;
}

//Class skills
/* @brief à améliorer
*/
sf::Vector2i Explorer::computePositionToExplore()
{
    /*
    //position of the Tile to get for the next completeMap()
    int x = -1;
    int y = -1;

    //variations applicated to this.pos to find a Tile to explorer as near as possible
    int d_x;
    int d_y;

    //if an unknown position is found, the loops are stopped with found
    bool found = false;

    //distance from this.pos
    for(int i=1; i<MAX_SIZE_X && i<MAX_SIZE_Y && !found; i++)
    {
        //distance from this.pos distributed between x and y axises
        for(int j=0; j<=i && !found; j++)
        {
            //distribution of distance depending on j
            d_x = i-j;
            d_y = j;

            //if the position is in the tab and hasn't been explored yet
            if((pos.x+d_x<MAX_SIZE_X) && (pos.y+d_y<MAX_SIZE_Y) && map[pos.x+d_x][pos.y+d_y]==-1)
            {
                x = pos.x+d_x;
                y = pos.y+d_y;
                found=true;
            }//not double check considering d_y==0, if the position is in the tab and hasn't been explored yet
            else if(d_y>0 && (pos.x+d_x<MAX_SIZE_X) && (pos.y-d_y>=0) && map[pos.x+d_x][pos.y-d_y]==-1)
            {
                x = pos.x+d_x;
                y = pos.y-d_y;
                found=true;
            }//not double check considering d_x==0, if the position is in the tab and hasn't been explored yet
            else if(d_x>0 && (pos.x-d_x>=0) && (pos.y+d_y<MAX_SIZE_Y) && map[pos.x+d_x][pos.y+d_y]==-1)
            {
                x = pos.x-d_x;
                y = pos.y+d_y;
                found=true;
            }//x==y==0 not possible so simply if the position is in the tab and hasn't been explored yet
            else if((pos.x-d_x>=0) && (pos.y-d_y>=0) && map[pos.x+d_x][pos.y+d_y]==-1)
            {
                x = pos.x-d_x;
                y = pos.y-d_y;
                found=true;
            }
        }
    }

    return sf::Vector2i(x,y);*/
}

void Explorer::completeMap()
{
    for(int d_x=1; x<visual_acuity; x++)
        for(int d_y=1; y<visual_acuity; y++)
        {
            int z;
            if(pos.x+d_x<MAX_SIZE_X && pos.y+d_y<MAX_SIZE_Y)
                z=0;//map[pos.x+d_x][pos.y+d_y]=savaleur;
            if(pos.x+d_x<MAX_SIZE_X && pos.y-d_y>=0)
                z=1;//map[pos.x+d_x][pos.y-d_y]=savaleur;
            if(pos.x-d_x>=0 && pos.y+d_y<MAX_SIZE_Y)
                z=2;//map[pos.x-d_x][pos.y+d_y]=savaleur;
            if(pos.x-d_x>=0 && pos.y-d_y>=0)
                z=3;//map[pos.x-d_x][pos.y-d_y]=savaleur;
        }

    notify(ref(this), E_REQ_EXPLORE_POSITION); //à réutiliser à chaque retour en état explorer
}
void Explorer::setExplorerObjective(std::vector<sf::Vector2i> obj);
{
    explorer_objective = obj;
}
