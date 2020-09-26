/**@file Game Manager header*/
#include <SFML/Graphics.hpp>
#include <SFML/Main.hpp>

/** @class GameManager
    @brief manages the game*/
class GameManager {
public:
  GameManager();
  ~GameManager();
  /**@brief initializes the game*/
  void init();
  /**@brief main loop of the game*/
  void mainloop();
private:
  sf::RenderWindow window;
};
