/** @file Game.h
 *  @brief File containing the Game class.
 *
 *  The purpose of this file is to implement a class that
 *  handles the game states in the application. 
 *
 *  @author Stephanie Li
 */

#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <stack>

class GameState;  //Allows Game to know about GameState

/** @brief Creates a Game.
 *  Game is a GameState manager that handles the changing
 *  of the states and info storage in every game state.
 */
class Game {
  public:
    Game();
    ~Game();

   /** @brief Stack for storing the game states.
    */
    std::stack<GameState*> game_states;

    /** @brief Main window for game.
     */
    sf::RenderWindow game_window;

    /** @brief Helper push function for GameState stack.
     *  @return Void.
     */
    void pushState(GameState *state);

    /** @brief Helper pop function for GameState stack.
     *  @return Void.
      */
    void popState();

    /** @brief Helper function for GameState stack to change
     *  previous state into given state.
     *  @return Void.
     */
    void changeState(GameState *state);

    /** @brief Helper peek function for GameState stack.
     *  @return Pointer to GameState that's on top of the stack.
     */
    GameState* peekState();

    /** @brief Drives the game
     *  @return Void.
     */
    void gameLoop();
};