#ifndef TILE_H
#define TILE_H


class Tile
{
    public:
        Tile();
        ~Tile();
        void setTile(char value);
        void emptyTile();
        int returnTileValue();
    protected:

    private:
        int tile_type;
        bool tile_is_empty;

};

#endif // TILE_H
