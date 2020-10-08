#include "TileMap.h"
#include "Tile.h"
#include "FileReader.h"
#include <iostream>

TileMap::TileMap()
{
    //ctor
}

TileMap::~TileMap()
{
    //dtor
}

void TileMap::setTab()
{
    FileReader f;
    char intermediate_tab[10][10];
    f.readFile(intermediate_tab);
    for(int i=0;i<=9;++i)
    {
        for(int j=0;j<=9;++j)
        {
            tilemap_tab[i][j].setTile(intermediate_tab[i][j]);
        }
    }
}

void TileMap::printTab()
{
    for(int i=0;i<=9;++i)
    {
        for(int j=0;j<=9;++j)
        {
            std::cout<<tilemap_tab[i][j].returnTileValue();
        }
        std::cout<<std::endl;
    }
}
