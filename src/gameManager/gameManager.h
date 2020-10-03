/**@file Game Manager header*/
#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

#include <SFML/Graphics.hpp>
#include <SFML/Main.hpp>
#include <memory>
#include <vector>
#include "component.h"
#include "Observer.h"

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
  virtual void on_Notify(Event event);
private:
  sf::RenderWindow window;
  std::vector<std::shared_ptr<Component>> components;
};

#endif
