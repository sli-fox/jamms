#include <gameStates/GameStateWin.h>

/**  The constructor sets the view to the size of the window
  *  and centers the view on the center of the window.
  */
GameStateWin::GameStateWin(Game* game) {
  this->game = game;
  
  // getSize() returns a sf::Vector2i object and must be cast into a sf::Vector2f
  sf::Vector2f position = sf::Vector2f(this->game->game_window.getSize());
  this->_view.setSize(position);

  sf::Vector2f center_position = 0.5f * position;
  this->_view.setCenter(center_position);
}

/**  This function sets the view to be drawn to the window
  *  and also calls a function to draw the splash screen.
  */
void GameStateWin::draw(const float delta_time) {
  this->game->game_window.setView(this->_view);
  this->game->game_window.clear(sf::Color::Black);
  this->game->game_window.draw(this->getGameWinScreenSprite());
}

void GameStateWin::handleInput() {
  sf::Event event;

  while(this->game->game_window.pollEvent(event)) {
    switch(event.type) {
      /** Close the window */
      case sf::Event::Closed: {
        game->game_window.close();
        break;
      }
      /** Go to main menu */
      case sf::Event::KeyPressed: {
        this->returnToMainMenu();
        break;
      }
      case sf::Event::MouseButtonPressed: {
        this->returnToMainMenu();
        break;
      }
      default: break;
    }
  }
}

/**  Add the GameStateMainMenu state to the game
  */
void GameStateWin::returnToMainMenu() {
  this->game->pushState(new GameStateMainMenu(this->game));
}


sf::Sprite GameStateWin::getGameWinScreenSprite() {
  TextureManager& t_manager = TextureManager::getInstance();
  sf::Sprite game_over_sprite(t_manager.loadTexture("resources/images/GameWinScreen.png"));
  return game_over_sprite;
}

