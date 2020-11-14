/**@file component header*/
#ifndef COMPONENT_H
#define COMPONENT_H

#include <SFML/Graphics.hpp>
#include <memory>

/**@class Component class
  @brief components of the GM class*/
class Component {
public:
  /**@brief class constructor*/
  Component();
  /**@brief class destructor*/
  virtual ~Component();
  /**@brief deactivate item*/
  void deactivate();
  /**@brief reactivate item*/
  void activate();
  /**@brief get active*/
  bool is_Active();
  /**@brief init method
  overwritten by children classes, called at gm init*/
  virtual void _init() = 0;
  /**@brief update method
  called every frame, updates game logic*/
  virtual void _update() = 0;
  /**@brief draw method
  called every frame, draws component on window
  @param window window to draw in*/
  virtual void _draw(sf::RenderWindow & window) = 0;
  bool active = true;
};

#endif
