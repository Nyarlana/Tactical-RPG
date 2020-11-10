#include "UI_TextBox.h"

UI_TextBox::UI_TextBox(sf::Vector2i pos, std::string txt, sf::Color text_col, sf::Color bg_col, std::string filename) : UI_Component(pos) {
  text.setString(txt);
  inner_text = txt;
  background.setFillColor(bg_col);
  text.setFillColor(text_col);
  font_file = filename;
  text.setCharacterSize(12);
}

void UI_TextBox::setText(std::string str) {
  text.setString(str);
}

void UI_TextBox::_init() {
  sf::Font font;
  if(!font.loadFromFile(font_file))
  {
    if(!font.loadFromFile("../"+font_file))
    {
      std::cout << "erreur" << '\n';
    }
  } else std::cout<<"font loaded"<<std::endl;


  text.setString(inner_text);
  text.setPosition(sf::Vector2f(position));
  sf::FloatRect rect = text.getGlobalBounds();
  background.setPosition(sf::Vector2f(rect.left, rect.top));
  background.setSize(sf::Vector2f(rect.width, rect.height));
  std::cout<<"r.left : "<<rect.left<<" | r.top : "<<rect.top<<"\nr.width : "<<rect.width<<" | rect.height : "<<rect.height<<std::endl;
}

void UI_TextBox::_update() {
  //pass
}

void UI_TextBox::_draw(sf::RenderWindow & window) {
  window.draw(background);
  window.draw(text);
}

void UI_TextBox::on_Notify(Component* subject, Event event) {
  //hello
}
