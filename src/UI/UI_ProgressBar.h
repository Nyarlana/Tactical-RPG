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
  @param border_sz width of border
  @param max_value_ maximum value of the bar
  @param value_ current value of the bar
  @param bg_col color of back of bar
  @param col color of front of bar
  @param border_col color of bar border*/
  UI_ProgressBar(sf::Vector2i pos, sf::Vector2i shape, float border_sz = 3, int max_value_ = 100, int value_ = 100, sf::Color bg_col = sf::Color::Red, sf::Color col = sf::Color::Green, sf::Color border_col = sf::Color::Black);
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
  virtual void on_Notify(Component* subject, Event event);
private:
  sf::Vector2i bar;
  float max_value;
  float value;
  float border_size;
  sf::Color background_color;
  sf::Color color;
  sf::Color border_color;
  //render object
  sf::RectangleShape background;
  sf::RectangleShape foreground;
  sf::RectangleShape border;
};

#endif
