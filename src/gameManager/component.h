/**@file component header*/
#ifndef COMPONENT_H
#define COMPONENT_H

class Component {
public:
  Component();
  virtual ~Component();
  virtual void _init() = 0;
  virtual void _update() = 0;
  virtual void _draw() = 0;
};

#endif
