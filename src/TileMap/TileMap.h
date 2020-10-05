#ifndef TILEMAP_H
#define TILEMAP_H
#include "FileReader.h"
#include "Tile.h"

class TileMap
{
    public:
        TileMap();
        ~TileMap();
        void setTab();
        void printTab();

    protected:

    private:
        Tile tilemap_tab[10][10];
};

#endif // TILEMAP_H
