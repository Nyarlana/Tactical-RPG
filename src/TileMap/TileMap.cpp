#include "TileMap.h"
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
    f.readFile(tilemap_tab);
}

void TileMap::printTab()
{
    for(int i=0;i<=9;++i)
    {
        for(int j=0;j<=9;++j)
        {
            std::cout<<tilemap_tab[i][j];
        }
        std::cout<<std::endl;
    }
}
