/**@file Tile header*/
#ifndef TILE_H
#define TILE_H

/**@class Tile
@brief Component of the TileMap class*/
class Tile
{
    public:
        /**@brief class constructor*/
        Tile();
        /**@brief class destructor*/
        ~Tile();
        /**@brief Given a char from the read file, sets a Tile with specific parameters*/
        void setTile(char value);
        /**@brief Sets bool tile_is_obstacle to true*/
        void setObstacle(bool b);
        /**@brief Temporary function, for testing*/
        int returnTileValue();
        /**@brief A**/
        bool returnTileObstacle();
    protected:

    private:
        int tile_type;
        bool tile_is_obstacle;

};

#endif // TILE_H
