#include "UI_VisualPath.h"

UI_VisualPath::UI_VisualPath(std::vector<sf::Vector2i> path) : UI_Component(sf::Vector2i(0,0)) {
  array = sf::VertexArray(sf::LineStrip);
  for (size_t i = 0; i < path.size(); i++) {
    array.append(sf::Vertex(sf::Vector2f(path[i].x*32+16, path[i].y*32+16)));
  }
}

void UI_VisualPath::add_To_Path(sf::Vector2i node) {
  array.append(sf::Vertex(sf::Vector2f(node.x*32+16,node.y*32+16)));
}

void UI_VisualPath::_init() {
  //code
}

void UI_VisualPath::_update() {
  /////
}

void UI_VisualPath::_draw(sf::RenderWindow & window) {
  window.draw(array);
}

void UI_VisualPath::on_Notify(Component* subject, Event event) {
  //pass
}
