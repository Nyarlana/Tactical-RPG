#include "UI_Point.h"

UI_Point::UI_Point(sf::Vector2i pos, sf::Color col) {
  position = pos*32+sf::Vector2i(13,13);
  shape.setSize(sf::Vector2f(6,6));
  shape.setPosition(sf::Vector2f(position));
  color = col;
  color.a = 128;
  shape.setFillColor(color);
}

void UI_Point::_init() {
  //code
}

void UI_Point::_update() {
  /////
}

void UI_Point::_draw(sf::RenderWindow & window) {
  window.draw(shape);
}

void UI_Point::on_Notify(Component* subject, Event event) {
  //pass
}
