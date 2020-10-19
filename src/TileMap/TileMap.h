/**@file Tile Map header*/
#ifndef TILEMAP_H
#define TILEMAP_H
#include <SFML/Graphics.hpp>
#include <vector>
#include "FileReader.h"
#include "../gameManager/Component.h"
#include "../gameManager/Observer.h"
#include "Tile.h"

/**@brief A* implementation
  Explored node, stocks where it came from*/
struct NodePath {
  sf::Vector2i node;
  NodePath * from;
  float hcost;
};

/**@class TileMap
@brief The map on which the game happens*/
class TileMap : public Component, public Observer, public Subject
{
    public:
        /**@brief Class constructor*/
        TileMap();
        /**@brief Class destructor*/
        ~TileMap();
        /**@brief Calls FileReader and sets the tilemap_tab with read values*/
        void setTab();
        /**@brief Temporary function, for testing*/
        void printTab();
        /**@brief A* implementation
        returns a path from start to end avoiding obstacles
        @param start starting position
        @param end ending position*/
        std::vector<sf::Vector2i> request_path(const sf::Vector2i & start,const sf::Vector2i & end);
        /**@brief A* implementation
        heuristics*/
        float heuristics(sf::Vector2i tile, sf::Vector2i start, sf::Vector2i end);
        /**@brief A* implementation*/
        void sortPath(std::vector<NodePath> & queue);
        /**@brief A* implementation*/
        std::vector<sf::Vector2i> makePath(const NodePath & from);
        /**@brief A* implementation*/
        bool isNotIn(const NodePath & current, const std::vector<NodePath> & explored);

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
