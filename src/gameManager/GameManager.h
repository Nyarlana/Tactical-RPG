/**@file Game Manager header*/
#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

#include <SFML/Graphics.hpp>
#include <SFML/Main.hpp>
#include <memory>
#include <vector>
#include "Component.h"
#include "Observer.h"
#include "../TileMap/TileMap.h"

/** @class GameManager
    @brief manages the game*/
class GameManager : public Observer {
public:
  /**@brief class constructor*/
  GameManager();
  /**@brief class destructor*/
  ~GameManager();
  /**@brief initializes the game*/
  void init();
  /**@brief main loop of the game*/
  void mainloop();
  /**@brief observer implementation*/
  virtual void on_Notify(const Component& subject, Event event);
private:
  sf::RenderWindow window;
  std::vector<Component*> components;
  TileMap * tm;
};

#endif
