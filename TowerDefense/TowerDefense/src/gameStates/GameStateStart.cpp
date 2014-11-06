#include <gameStates/GameStateStart.h>

/**  The constructor sets the view to the size of the window
  *  and centers the view on the center of the window.
  */
GameStateStart::GameStateStart(Game* game) {
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
void GameStateStart::draw(const float delta_time) {
  this->game->game_window.setView(this->_view);
  this->game->game_window.clear(sf::Color::Black);
  this->game->game_window.draw(this->getSplashScreenSprite());
}

void GameStateStart::handleInput() {
  sf::Event event;

  while(this->game->game_window.pollEvent(event)) {
    switch(event.type) {
      /** Close the window */
      case sf::Event::Closed: {
        game->game_window.close();
        break;
      }
      /** Start the game */
      case sf::Event::KeyPressed: {
        this->loadMainMenu();
        break;
      }
      case sf::Event::MouseButtonPressed: {
        this->loadMainMenu();
        break;
      }
      default: break;
    }
  }
}

/**  Add the GameStateMainMenu state to the game
  */
void GameStateStart::loadMainMenu() {
  this->game->pushState(new GameStateMainMenu(this->game));
}

sf::Sprite GameStateStart::getSplashScreenSprite() {
  TextureManager& t_manager = TextureManager::getInstance();
  sf::Sprite splash_screen_sprite(t_manager.loadTexture("resources/images/SplashScreen.png"));
  return splash_screen_sprite;
}

