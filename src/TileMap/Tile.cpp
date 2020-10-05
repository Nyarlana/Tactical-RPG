#include "Tile.h"

Tile::Tile()
{
    //ctor
}

Tile::~Tile()
{
    //dtor
}

void Tile::setTile(char value)
{
    tile_type = static_cast<int>(value)-48;
    tile_is_empty = (tile_type == 0);
}

void Tile::emptyTile()
{
    tile_is_empty = true;
}

int Tile::returnTileValue()
{
    return tile_type;
}
