#include "UI_Component.h"

#ifndef UI_VISUALPATH
#define UI_VISUALPATH

/**@class UI_VisualPath
@brief displays an inner path using grid coordinates*/
class UI_VisualPath : public UI_Component {
public:
  /**@brief class constructor*/
  UI_VisualPath(std::vector<sf::Vector2i> path);
  /**@brief add to path*/
  void add_To_Path(sf::Vector2i node);
  // inheritance
  virtual void _init();
  virtual void _update();
  virtual void _draw(sf::RenderWindow & window);
  virtual void on_Notify(Component* subject, Event event);
private:
  sf::VertexArray array;
};

#endif
