#ifndef TILEMAP_H
#define TILEMAP_H
#include "FileReader.h"
#include "../gameManager/Component.h"
#include "../gameManager/Observer.h"
#include "Tile.h"

class TileMap : public Component, public Observer, public Subject
{
    public:
        TileMap();
        ~TileMap();
        void setTab();
        void printTab();
        // Surcharge
        virtual void on_Notify(const Component& subject, Event event);
        virtual void _init();
        virtual void _update();
        virtual void _draw(sf::RenderWindow & window);

    protected:

    private:
        Tile tilemap_tab[10][10];
};

#endif // TILEMAP_H
