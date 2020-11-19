/**@file Tile Map header*/
#define TM_X_TAB 25
#define TM_Y_TAB 25
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
        /**@brief testing func*/
        void testFunc();
        /**@brief A* implementation
        returns a path from start to end avoiding obstacles
        @param start starting position
        @param end ending position
        @return sorted path*/
        std::vector<sf::Vector2i> request_path(const sf::Vector2i & start,const sf::Vector2i & end);
        /**@brief heuristics
        calculate heuristics depending on distance to start and end
        @param tile position to calculate distance from
        @param start starting position
        @param end ending position*/
        float heuristics(sf::Vector2i tile, sf::Vector2i start, sf::Vector2i end);
        /**@brief sorts NodePath
        A* implementation, sorts queue depending on NodePath hcost
        @param queue array to sort*/
        void sortPath(std::vector<NodePath> & queue);
        /**@brief create path
        A* implementation, return a path of 2d points from the endpoint node
        @param from last NodePath explored
        @param start position of the first point*/
        std::vector<sf::Vector2i> makePath(const NodePath & from, const sf::Vector2i & start);
        /**@brief checks array for NodePath
          A* implementation
          @param current Node to search
          @param explored array to search in*/
        bool isNotIn(const NodePath & current, const std::vector<NodePath> & explored);
        /**@brief checks if the given position is in the TileMap
          @param x x value of the position to test
          @param y y value of the position to test*/
        bool isInMap(int x, int y);
        /**@brief Gives a random correct move
        @param pos base position from where to move
        @return the given move*/
        std::vector<sf::Vector2i> getRandomMove(sf::Vector2i pos);
        /**@brief Gives a random position thats valid in the TileMap
        @return a valid position*/ 
        sf::Vector2i getRandomValidPosition();
        /**@brief Gives positions of ores around pos within radius
        @param pos base position from where to look for
        @param radius max distance from pos to look
        @return a list of positions*/
        std::vector<sf::Vector2i> lookForOre(sf::Vector2i pos, int radius);
        /**@brief transforms the Tile at position pos to an empty tile
        @param pos position where the ore is mined*/
        void mine(sf::Vector2i pos);

        // Surcharge
        virtual void on_Notify(Component* subject, Event event);
        virtual void _init();
        virtual void _update();
        virtual void _draw(sf::RenderWindow & window);

    protected:

    private:
        Tile tilemap_tab[TM_X_TAB][TM_Y_TAB];
        sf::Texture tile_texture;
        sf::Sprite empty_tile_sprite;
        sf::Sprite full_tile_sprite;
        sf::Sprite resource_tile_sprite;
        sf::Sprite resource2_tile_sprite;
};

#endif // TILEMAP_H
