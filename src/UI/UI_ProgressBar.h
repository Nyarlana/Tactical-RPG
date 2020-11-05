#include "UI_Component.h"

#ifndef UI_PROGRESSBAR
#define UI_PROGRESSBAR

/**@class UI_ProgressBar
  @brief Overlapping bars representing a progressing value*/
class UI_ProgressBar : public UI_Component
{
public:
  /**@brief constructor
  @param pos position
  @param bar dimensions of the form
  @param max_value_ maximum value of the bar
  @param value_ current value of the bar
  @param bg_col color of back of bar
  @param col color of front of bar*/
  UI_ProgressBar(sf::Vector2i pos, sf::Vector2i shape, int max_value_ = 100, int value_ = 100, sf::Color bg_col = sf::Color::Red, sf::Color col = sf::Color::Green);
  /**@brief add to inner value
  @param plus value to add*/
  void add_Value(const int plus);
  /**@brief substract from inner value
  @param minus value to substract*/
  void substract_Value(const int minus);
  /**@brief set value, ignoring caps
  @param value value to set*/
  void set_Value(const int val);
  /**@brief background color setter
  @param col color*/
  void set_Background_Color(const sf::Color & col);
  /**@brief foreground color setter
  @param col color*/
  void set_Foreground_Color(const sf::Color & col);
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
