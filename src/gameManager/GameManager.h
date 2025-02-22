/**@file Game Manager header*/
#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

#include <SFML/Graphics.hpp>
#include <SFML/Main.hpp>
#include <memory>
#include <vector>
#include <mutex>
#include <thread>
#include "Component.h"
#include "Observer.h"
#include "ThreadContainer.h"
#include "../TileMap/TileMap.h"
#include "../UI/UI.h"
#include "../entities/entities.h"

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
  virtual void on_Notify(Component* subject, Event event);
  /**@brief add a component
  @param comp pointer to component to add*/
  void add_Component(const std::shared_ptr<Component> comp);
  /**@brief test function*/
  void testFunc();
  /**@brief */
  void setRoverBase(std::string mission);
  /**@brief */
  void addAlienGroup(int alien_number, int alien_average_stats);
  /**@brief computes and sets an entity's path to a target position
  @param e pointer to the entity which path needs to be compute and set
  @param e_target position of the target*/
  void compute_and_set_path(Entity* e, sf::Vector2i e_target);

private:
  sf::RenderWindow window;
  std::vector<std::shared_ptr<Component>> components;
  std::shared_ptr<TileMap> tm;
  std::shared_ptr<UI_ProgressBar> pb;
  std::shared_ptr<UI_TextBox> tb;
  std::shared_ptr<UI_VisualPath> vp;
  std::shared_ptr<UI_Point> start;
  std::shared_ptr<UI_Point> finish;
  std::vector<std::thread> entities;
  std::vector<std::shared_ptr<AlienGroup>> ag;
  std::shared_ptr<RoverBase> rb;
  std::mutex* m;
};

#endif
