#include "UI_ProgressBar.h"

UI_ProgressBar::UI_ProgressBar(sf::Vector2i pos, sf::Vector2i shape, int max_value_, int value_, sf::Color bg_col, sf::Color col) {
  position = pos;
  bar = shape;
  max_value = max_value_;
  value = value_;
  background_color = bg_col;
  color = col;
}

void UI_ProgressBar::_init() {
  //code
}

void UI_ProgressBar::_update() {
  background.setPosition(sf::Vector2f(position));
  background.setSize(sf::Vector2f(bar));
  background.setFillColor(background_color);

  foreground.setPosition(sf::Vector2f(position));
  foreground.setSize(sf::Vector2f(bar.x*(value/max_value), bar.y));
  foreground.setFillColor(color);
}

void UI_ProgressBar::_draw(sf::RenderWindow & window) {
  window.draw(background);
  window.draw(foreground);
}

void UI_ProgressBar::on_Notify(const Component* subject, Event event) {
  //hello !!
}
