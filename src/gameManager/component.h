/**@file component header*/
#ifndef COMPONENT_H
#define COMPONENT_H

#include <SFML/Graphics.hpp>

class Component {
public:
  Component();
  virtual ~Component();
  virtual void _init() = 0;
  virtual void _update() = 0;
  virtual void _draw(sf::RenderWindow & window) = 0;
};

#endif
