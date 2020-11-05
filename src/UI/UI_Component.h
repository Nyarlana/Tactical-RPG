#include "../gameManager/Observer.h"
#include "../gameManager/Component.h"
#include "../gameManager/GameManager.h"
#include <SFML/Graphics.hpp>

#ifndef UI_COMPONENT
#define UI_COMPONENT

/**@class UI_Component
  @brief generic class for all UI Components*/
class UI_Component : public Observer, public Subject, public Component
{
public:
  /**@brief empty constructor
  inheritance purposes*/
  UI_Component();
  /**@brief constructor
  @param pos position*/
  UI_Component(sf::Vector2i pos);
  /**@brief position setter
  @param pos position*/
  void set_Position(sf::Vector2i pos);
protected:
  sf::Vector2i position;
};
#endif
