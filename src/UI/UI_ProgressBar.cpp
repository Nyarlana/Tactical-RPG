#include "UI_ProgressBar.h"

UI_ProgressBar::UI_ProgressBar(sf::Vector2i pos, sf::Vector2i shape, int max_value_, int value_, sf::Color bg_col, sf::Color col) : UI_Component(pos) {
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

void UI_ProgressBar::add_Value(const int plus) {
  value += plus;
  if (value > max_value) {
    value = max_value;
  } else if (value < 0) {
    value = 0;
  }
}

void UI_ProgressBar::substract_Value(const int minus) {
  add_Value(-minus);
}

void UI_ProgressBar::set_Value(const int val) {
  value = val;
}

void UI_ProgressBar::set_Background_Color(const sf::Color & col) {
  background_color = col;
}

void UI_ProgressBar::set_Foreground_Color(const sf::Color & col) {
  color = col;
}
