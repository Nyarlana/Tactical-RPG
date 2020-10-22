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
    tile_is_obstacle = (tile_type != 0);
}

void Tile::setObstacle(bool b)
{
    tile_is_obstacle = b;
}

int Tile::returnTileValue()
{
    return tile_type;
}

bool Tile::returnTileObstacle()
{
  return tile_is_obstacle;
}
