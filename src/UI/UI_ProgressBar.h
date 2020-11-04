#include "UI_Component.h"

#ifndef UI_PROGRESSBAR
#define UI_PROGRESSBAR

class UI_ProgressBar : public UI_Component
{
public:
  /**@brief constructor
  @param pos position
  @param bar dimensions of the form
  @param max_value_ maximum value of the bar
  @param value_ current value of the bar*/
  UI_ProgressBar(sf::Vector2i pos, sf::Vector2i shape, int max_value_ = 100, int value_ = 100, sf::Color bg_col = sf::Color::Red, sf::Color col = sf::Color::Green);
  //surcharge
  virtual void _init();
  virtual void _update();
  virtual void _draw(sf::RenderWindow & window);
  virtual void on_Notify(const Component* subject, Event event);
private:
  sf::Vector2i bar;
  float max_value;
  float value;
  sf::Color background_color;
  sf::Color color;
  //render object
  sf::RectangleShape background;
  sf::RectangleShape foreground;
};

#endif
