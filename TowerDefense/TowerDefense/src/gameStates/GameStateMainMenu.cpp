#include <gameStates/GameStateMainMenu.h>

/**  The constructor sets the view to the size of the window
  *  and centers the view on the center of the window.
  */
GameStateMainMenu::GameStateMainMenu(Game* game) {
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
void GameStateMainMenu::draw(const float delta_time) {
  this->game->game_window.setView(this->_view);
  this->game->game_window.clear(sf::Color::Black);
  MainMenu main_menu;
  selected_action = main_menu.show(this->game->game_window);
}

void GameStateMainMenu::update(const float delta_time) {

}

void GameStateMainMenu::handleInput() {
  switch(selected_action) {
  case::MainMenu::EXIT:
    game->game_window.close();
    break;
  case::MainMenu::PLAY:
    this->loadGame();
    break;
  }
}

/**  Add the GameStatePlay state to the game
  */
void GameStateMainMenu::loadGame() {
  this->game->pushState(new GameStatePlay(this->game));
}

void GameStateMainMenu::handleSelectedAction() {
  
}

