#include "UI_Component.h"
#include <string>
#include <iostream>

#ifndef UI_TEXTBOX
#define UI_TEXTBOX

/**@class UI_TextBox
  @brief rendered line of text w/ a background*/
class UI_TextBox : public UI_Component
{
public:
  /**@brief constructor
    @param pos position
    @param text text to display
    @param text_col color of text
    @param bg_col color of background
    @param filename adress of font*/
  UI_TextBox(sf::Vector2i pos, std::string text, sf::Color text_col = sf::Color::Black, sf::Color bg_col = sf::Color(255,255,255,128), std::string filename = "data/font.ttf");
  /**@brief sets inner text
  @param str string to display*/
  void setText(std::string str);
  //surcharge
  virtual void _init();
  virtual void _update();
  virtual void _draw(sf::RenderWindow & window);
  virtual void on_Notify(Component* subject, Event event);
private:
  sf::RectangleShape background;
  sf::Text text;
  std::string font_file;
  std::string inner_text;
};

#endif
