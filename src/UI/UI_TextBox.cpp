#include "UI_TextBox.h"

UI_TextBox::UI_TextBox(sf::Vector2i pos, std::string txt, int font_size, sf::Vector2i mar, sf::Color text_col, sf::Color bg_col, std::string filename) : UI_Component(pos) {
  text.setString(txt);
  inner_text = txt;
  background.setFillColor(bg_col);
  text.setFillColor(text_col);
  if(!font.loadFromFile(filename))
  {
    if(!font.loadFromFile("../"+filename))
    {
      std::cout << "erreur" << '\n';
    }
  } else std::cout<<"font loaded"<<std::endl;
  text.setCharacterSize(font_size);
  text.setFont(font);
  margins = sf::Vector2f(mar);
}

void UI_TextBox::setText(std::string str) {
  text.setString(str);
  sf::FloatRect rect = text.getGlobalBounds();
  background.setSize(sf::Vector2f(rect.width, rect.height)+margins+margins);
}

std::string UI_TextBox::getText() {
  return text.getString();
}

void UI_TextBox::set_Position(sf::Vector2i pos) {
  position = pos;
  text.setPosition(sf::Vector2f(position)+margins);
  background.setPosition(sf::Vector2f(text.getGlobalBounds().left, text.getGlobalBounds().top)-margins);
}

void UI_TextBox::_init() {
  text.setString(inner_text);
  text.setPosition(sf::Vector2f(position));
  sf::FloatRect rect = text.getGlobalBounds();
  background.setPosition(sf::Vector2f(rect.left, rect.top)-margins);
  background.setSize(sf::Vector2f(rect.width, rect.height)+margins+margins);
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
