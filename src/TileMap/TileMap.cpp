#include "TileMap.h"

#include <iostream>
#include <set>
#include <algorithm>
#include <math.h>

TileMap::TileMap() : m(new std::mutex())
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

    // std::cout << intermediate_tab[TM_X_TAB][TM_Y_TAB] << '\n';
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

void TileMap::on_Notify(Component* subject, Event event)
{
  switch (event)
  {
    case E_MOVED:
    {
        std::shared_ptr<Entity> e = std::dynamic_pointer_cast<Entity>(
            ((Entity*) subject)->shared_from_this()
        );

        std::unordered_map<std::shared_ptr<Entity>, sf::Vector2i>::const_iterator got = entities.find(e);

        if(got == entities.end())
            entities.emplace(e, e->getPos());
        else
            entities[e]=e->getPos();
        break;
    }
    case E_DIED:
    {
        std::shared_ptr<Entity> e = std::dynamic_pointer_cast<Entity>(
            ((Entity*) subject)->shared_from_this()
        );

        entities.erase(e);
        break;
    }
  }
}

void TileMap::_init()
{
  setTab();

  if(!tile_texture.loadFromFile("data/tile/tile_final.png"))
  {
    if(!tile_texture.loadFromFile("../data/tile/tile_final.png"))
    {
      std::cout << "erreur" << '\n';
    }
  }

  empty_tile_sprite.setTexture(tile_texture);
  empty_tile_sprite.setTextureRect(sf::IntRect(0,0,32,32));
  full_tile_sprite.setTexture(tile_texture);
  full_tile_sprite.setTextureRect(sf::IntRect(32,0,32,32));
  resource_tile_sprite.setTexture(tile_texture);
  resource_tile_sprite.setTextureRect(sf::IntRect(64,0,32,32));
  resource2_tile_sprite.setTexture(tile_texture);
  resource2_tile_sprite.setTextureRect(sf::IntRect(96,0,32,32));
}

void TileMap::_update()
{

}

void TileMap::_draw(sf::RenderWindow & window)
{
  for(int j=0; j<TM_X_TAB; ++j)
  {
    for(int i=0; i<TM_Y_TAB; ++i)
    {
      switch(tilemap_tab[i][j].returnTileValue())
      {
        case 0:
          empty_tile_sprite.setPosition(i*32,j*32);
          window.draw(empty_tile_sprite);
          break;
        case 1:
          full_tile_sprite.setPosition(i*32,j*32);
          window.draw(full_tile_sprite);
          break;
        case 2:
          if(tilemap_tab[i][j].returnTileObstacle())
          {
            resource_tile_sprite.setPosition(i*32,j*32);
            window.draw(resource_tile_sprite);
          }
          else
          {
            resource2_tile_sprite.setPosition(i*32,j*32);
            window.draw(resource2_tile_sprite);
          }
      }
      /*if(j>10)
      {
        empty_tile_sprite.setPosition(i*32,j*32);
        window.draw(empty_tile_sprite);
      }
      else
      {
        full_tile_sprite.setPosition(i*32,j*32);
        window.draw(full_tile_sprite);
      }*/
    }
  }
}

//A* implementation

std::vector<sf::Vector2i> TileMap::request_path(const sf::Vector2i& start,const sf::Vector2i& end)
{
  std::unique_lock<std::mutex> l(*m);
  std::cout << "----- Computing path from "<<start.x<<'|'<<start.y<<" to "<<end.x<<'|'<<end.y<<" -----" << '\n';
  //exceptions
  std::vector<sf::Vector2i> empty;
  if (tilemap_tab[end.x][end.y].returnTileObstacle()
  || tilemap_tab[start.x][start.y].returnTileObstacle())
  {
    std::cout << "  empty path returned" << '\n';
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
    if (queue.back().from != 0) {
      std::cout << "  inserting node "<<queue.back().node.x<<'|'<<queue.back().node.y << " from "<<queue.back().from->node.x<<'|'<<queue.back().from->node.y<< '\n';
    } else {
      std::cout << "  inserting node "<<queue.back().node.x<<'|'<<queue.back().node.y << '\n';
    }
    explored.push_back(queue.back());
    for (int i = -1; i <= 1; i++)
    {
      for (int j = -1; j <= 1; j++)
      {
        if (isInMap(queue.back().node.x + i, queue.back().node.y + j) &&
        !tilemap_tab[queue.back().node.x+i][queue.back().node.y+j].returnTileObstacle())
          {
            // current update
            current.node = sf::Vector2i(queue.back().node.x + i, queue.back().node.y + j);
            current.from = &explored.back();
            current.hcost = heuristics(current.node, start, end);
            //update vectors
            if (current.node != queue.back().node && isNotIn(current, explored) && isInMap(current.node.x, current.node.y))
            {
              std::cout << "    added " << current.node.x << '|' << current.node.y << " from : "<<current.from->node.x<<'|'<<current.from->node.y<< '\n';
              queue.insert(queue.end()-1,current);
            }
          }
      }
    }
    // update vectors
    queue.pop_back();
    sortPath(queue);
    if (queue.empty()) {
      return empty;
    }
  }
  //return
  std::cout << "start = " <<start.x<<", "<<start.y<< '\n';
  std::cout << "end   = " <<end.x<<", "<<end.y<< '\n';

  // NodePath end_node;
  // current.node = end;
  // current.from = &explored.back();
  // current.hcost = heuristics(end, start, end);
  //
  // explored.push_back(end_node);

  empty = makePath(explored.back(), start);

  for(int i=0; i<empty.size(); i++)
    std::cout << "return node -> ("<<empty[i].x<<";"<<empty[i].y<<")"<< '\n';

  return empty;
}

float TileMap::heuristics(sf::Vector2i tile, sf::Vector2i start, sf::Vector2i end)
{
  return sqrt((tile.x-end.x)*(tile.x-end.x) + (tile.y-end.y)*(tile.y-end.y)) +
        sqrt((tile.x-start.x)*(tile.x-start.x) + (tile.y-start.y)*(tile.y-start.y));
}

void TileMap::sortPath(std::vector<NodePath> & queue)
{
  sort(queue.rbegin(), queue.rend());
}

std::vector<sf::Vector2i> TileMap::makePath(const NodePath & from, const sf::Vector2i & start)
{
  std::vector<sf::Vector2i> res;
  NodePath current = from;
  std::cout << "return path : " << '\n';

  while (res.size()==0 || res.back() != start)
  {
    res.push_back(current.node);
    std::cout << current.node.x << '|' << current.node.y << " -> " << current.from->node.x<<'|'<<current.from->node.y<< '\n';

    if(!isInMap(current.from->node.x,current.from->node.y))
        res.push_back(start);
    else
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

bool TileMap::isInMap(int x, int y)
{
    return x>=0 && y>=0 && x<TM_X_TAB && y<TM_Y_TAB;
}

std::vector<sf::Vector2i> TileMap::getRandomMove(sf::Vector2i pos)
{
    sf::Vector2i arrivee;

    do {
        arrivee = sf::Vector2i(pos.x + rand()%3-1,pos.y + rand()%3-1);
    }
    while(!isInMap(arrivee.x, arrivee.y) ||
            (arrivee==pos) ||
            tilemap_tab[arrivee.x][arrivee.y].returnTileObstacle());

    std::vector<sf::Vector2i> path;
    path.push_back(arrivee);

    return path;
}

sf::Vector2i TileMap::getRandomValidPosition()
{
    int valid_pos_nb = 0;

    for(int i=0;i<TM_X_TAB;++i)
    {
        for(int j=0;j<TM_Y_TAB;++j)
        {
            if(tilemap_tab[i][j].returnTileValue()==0)
            {
                valid_pos_nb++;
            }
        }
    }

    int pos_to_give = (rand()%valid_pos_nb)+1;
    int x=0,y=0;

    for(int i=0;i<TM_X_TAB;++i)
    {
        for(int j=0;j<TM_Y_TAB;++j)
        {
            if(tilemap_tab[i][j].returnTileValue()==0)
            {
                pos_to_give--;

                if(pos_to_give==0)
                {
                    x=i;
                    y=j;
                }
            }
        }
    }

    return sf::Vector2i(x,y);
}

std::vector<sf::Vector2i> TileMap::lookForOre(sf::Vector2i pos, int radius)
{
    std::vector<sf::Vector2i> positions;

    for(int i=-radius; i<=radius; i++)
    {
        for(int j=-radius; j<=radius; j++)
        {
            if((i!=0 || j!=0)
                && (i+j!=0 && i+j!=radius*2 && i+j!=-(radius*2))
                && isInMap(i+pos.x, j+pos.y)
                && tilemap_tab[i+pos.x][j+pos.y].returnTileValue()==2
            )
                positions.push_back(sf::Vector2i(i+pos.x, j+pos.y));
        }
    }

    return positions;
}

bool TileMap::mine(sf::Vector2i pos)
{
    std::unique_lock<std::mutex> l(*m);

    if(tilemap_tab[pos.x][pos.y].returnTileValue()==2)
    {
        tilemap_tab[pos.x][pos.y].setTile('0');
        return true;
    }

    return false;
}
