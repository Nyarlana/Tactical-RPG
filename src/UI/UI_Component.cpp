#include "UI_Component.h"

UI_Component::UI_Component() {
  //useless
}

UI_Component::UI_Component(sf::Vector2i pos) {
  position = pos;
}

void UI_Component::set_Position(sf::Vector2i pos) {
  position = pos;
}
