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
    @param font_size size of font
    @param text_col color of text
    @param bg_col color of background
    @param filename adress of font*/
  UI_TextBox(sf::Vector2i pos, std::string text,int font_size = 24, sf::Vector2i mar = sf::Vector2i(2,2), sf::Color text_col = sf::Color::White, sf::Color bg_col = sf::Color(0,0,0,100), std::string filename = "data/font.ttf");
  /**@brief sets inner text
  @param str string to display*/
  void setText(std::string str);
  /**@brief text getter*/
  std::string getText();
  //surcharge
  virtual void _init();
  virtual void _update();
  virtual void _draw(sf::RenderWindow & window);
  virtual void on_Notify(Component* subject, Event event);
  virtual void set_Position(sf::Vector2i pos);
private:
  sf::RectangleShape background;
  sf::Text text;
  sf::Font font;
  std::string inner_text;
  sf::Vector2f margins;
};

#endif
