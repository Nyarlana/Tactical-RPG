#include "UI_Component.h"

#ifndef UI_POINT
#define UI_POINT

/**@class UI_VisualPath
@brief displays selected tile with a small square*/
class UI_Point : public UI_Component {
public:
  /**@brief class constructor
  @param pos position in grid coordinates
  @color color of the square (alpha will be set)*/
  UI_Point(sf::Vector2i pos, sf::Color col = sf::Color::Red);
  // inheritance
  virtual void _init();
  virtual void _update();
  virtual void _draw(sf::RenderWindow & window);
  virtual void on_Notify(Component* subject, Event event);
private:
  sf::RectangleShape shape;
  sf::Color color;
};

#endif
