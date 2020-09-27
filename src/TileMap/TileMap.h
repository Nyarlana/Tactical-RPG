#ifndef TILEMAP_H
#define TILEMAP_H
#include "FileReader.h"

class TileMap
{
    public:
        TileMap();
        virtual ~TileMap();
        void setTab();
        void printTab();

    protected:

    private:
        char tilemap_tab[10][10];
};

#endif // TILEMAP_H
