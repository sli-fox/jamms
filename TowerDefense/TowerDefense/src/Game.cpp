#include <Game.h>
#include <gameStates/GameState.h>
#include <gameStates/GameStatePlay.h>

/** @brief Constructor of Game sets the game window properties
 *  and frame rate.
 */

Map Game::map = Map(Map::MAX_MAP_WIDTH, Map::MAX_MAP_HEIGHT);
Player Game::player = Player("Jamms", 500);

Game::Game() {
  this->game_window.create(sf::VideoMode(1024, 768, 32), "Tower Defense", sf::Style::Close);
  this->game_window.setFramerateLimit(60);
  this->isGamePaused = false;
}

/** @brief Destructor of Game removes all GameStates from game states stack.
 */
Game::~Game() {
  while (!this->game_states.empty())
    popState();
}

void Game::pushState(GameState *state) {
  this->game_states.push(state);
}

void Game::popState() {  
  delete this->game_states.top();
  this->game_states.pop();
}

void Game::changeState(GameState *state) {
  if (!this->game_states.empty())
    popState();
  pushState(state);
}

GameState* Game::peekState() {
  if (this->game_states.empty())
    return nullptr;
  return this->game_states.top();
}

/** This function controls the speed of the logic in the game
 *  and passes it to any function that needs it. since gameLoop() 
 *  is called every frame, this function starts the clock at the 
 *  beginning of the frame, stops it at the end and calculates the 
 *  elapsed time. 
 *
 *  The functions from GameState are then called to draw updates to
 *  the render window.
 */
void Game::gameLoop() {
  /** Calculate elapsed time */
  sf::Clock clock;  //Clock starts automatically after being constructed

  while (this->game_window.isOpen()) {
    sf::Time elapsed_time = clock.restart();  //Resets clock and returns elapsed time since clock was started
    this->delta_time = elapsed_time.asSeconds();

    if (peekState() == nullptr) 
      continue;   //If there is no next state, skip the rest of the statements in the while

    /** Draw updates to render window */
    peekState()->handleInput();
    
    if (!this->isGamePaused)
      peekState()->update(delta_time);

    this->game_window.clear(sf::Color::Black);  //Make sure window is cleared before drawing updates.
    peekState()->draw(delta_time);
    this->game_window.display();
  }
  return;
}
