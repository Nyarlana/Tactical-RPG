#include "TileMap.h"
#include "Tile.h"
#include "FileReader.h"
#include <iostream>
#include <set>
#include <algorithm>
#include <math.h>

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
    char intermediate_tab[TM_X_TAB][TM_Y_TAB];
    f.readFile(intermediate_tab);

    for(int j=0;j<TM_Y_TAB;++j)
    {
        for(int i=0;i<TM_X_TAB;++i)
        {
            tilemap_tab[i][j].setTile(intermediate_tab[i][j]);
        }
    }
}

void TileMap::printTab()
{
    for(int i=0;i<TM_X_TAB;++i)
    {
        for(int j=0;TM_Y_TAB;++j)
        {
            std::cout<<tilemap_tab[i][j].returnTileValue();
        }
        std::cout<<std::endl;
    }
}

void TileMap::testFunc()
{
  notify((Component*) this,EVENT_TEST);
}

void TileMap::on_Notify(const Component* subject, Event event)
{
  switch (event) {
    case EVENT_TEST: printf("hello\n");
  }
}

void TileMap::_init()
{

  if(!tile_texture.loadFromFile("data/tile/tile_test.png"))
  {
    if(!tile_texture.loadFromFile("../data/tile/tile_test.png"))
    {
      //error
    }
  }
  tile_sprite.setTexture(tile_texture);
}

void TileMap::_update() {

}

void TileMap::_draw(sf::RenderWindow & window)
{
  for(int j=0; j<TM_X_TAB; ++j)
  {
    for(int i=0; i<TM_Y_TAB; ++i)
    {
      tile_sprite.setPosition(i*32,j*32);
      window.draw(tile_sprite);
    }
  }
}

//A* implementation

std::vector<sf::Vector2i> TileMap::request_path(const sf::Vector2i& start,const sf::Vector2i& end)
{
  //exceptions
  std::vector<sf::Vector2i> empty;
  if (tilemap_tab[end.x][end.y].returnTileObstacle())
  {
    return empty;
  }
  //used variables
  std::vector<NodePath> queue;
  std::vector<NodePath> explored;
  NodePath current;
  //add first node
  current.node = start;
  current.from = 0;
  current.hcost = heuristics(start, start, end);
  queue.push_back(current);
  //loop
  while (queue.back().node != end)
  {
    for (int i = -1; i <= 1; i++)
    {
      for (int j = -1; j <= 1; j++)
      {
        if ((queue.back().node.x + i >= 0) && (queue.back().node.x + i < 10) &&
          (queue.back().node.y + i >= 0) && (queue.back().node.y + i < 10))
          {
            // current update
            current.node = sf::Vector2i(queue.back().node.x + i, queue.back().node.y + j);
            current.from = &queue.back();
            current.hcost = heuristics(current.node, start, end);
            //update vectors
            if (current.node != queue.back().node && isNotIn(current, explored))
            {
              queue.insert(queue.end()-1,current);
            }
          }
      }
    }
    // update vectors
    explored.push_back(queue.back());
    queue.pop_back();
    sortPath(queue);
  }
  //return
  return makePath(explored.back(), start);
}

float TileMap::heuristics(sf::Vector2i tile, sf::Vector2i start, sf::Vector2i end)
{
  return sqrt((tile.x-end.x)*(tile.x-end.x) + (tile.y-end.y)*(tile.y-end.y)) +
        sqrt((tile.x-start.x)*(tile.x-start.x) + (tile.y-start.y)*(tile.y-start.y));
}

void TileMap::sortPath(std::vector<NodePath> & queue)
{
  sort(queue.rend(), queue.rbegin());
}

std::vector<sf::Vector2i> TileMap::makePath(const NodePath & from, const sf::Vector2i & start)
{
  std::vector<sf::Vector2i> res;
  NodePath current = from;
  while (current.node != start)
  {
    res.push_back(current.node);
    current = (*current.from);
  }
  return res;
}

bool TileMap::isNotIn(const NodePath & current, const std::vector<NodePath> & explored)
{
  for (size_t i = 0; i < explored.size(); i++)
  {
    if (explored[i].node == current.node)
    {
      return false;
    }
  }
  return true;
}

bool operator > (const NodePath & a,const NodePath & b)
{
  return a.hcost > b.hcost;
}

bool operator < (const NodePath & a,const NodePath & b)
{
  return a.hcost < b.hcost;
}
