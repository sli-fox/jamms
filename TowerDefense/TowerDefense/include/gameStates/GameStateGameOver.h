/** @file GameStateGameOver.h
 *  @brief File containing the GameStateGameOver class.
 *
 *  The purpose of this file is to implement a class that
 *  is a concrete game state representing the "game over" state. 
 *
 *  @author Stephanie Li
 */

#pragma once
#include <SFML/Graphics.hpp>
#include <gameStates/GameState.h>
#include <gameStates/GameStateMainMenu.h>
#include <managers/TextureManager.h>

/** @brief Game state that represents the game start,
 *  including the main game menu.
 */
class GameStateGameOver : public GameState {
  public:
    /** @brief Constructor that takes in a pointer to the Game
     *  that created them.
     *  @param game Pointer to game.
     */
    GameStateGameOver(Game* game);

    /** @brief Draws game to the render window. 
    *   @param delta_time Elapsed time during the game.
    *   @return Void.
    */
    virtual void draw(const float delta_time);
    
    /** @brief Updates game changes. 
    *   @param delta_time Elapsed time during the game.
    *   @return Void.
    */
    virtual void update(const float delta_time) {};
    
    /** @brief Handles player input. 
    *   @return Void.
    */
    virtual void handleInput();

    virtual void runThreads() {};

  private:
    /** @brief Camera view for the GameState displayed to the window.
    */
    sf::View _view;

    /** @brief Function that transitions to the GameStateMainMenu state. 
    *   @return Void.
    */
    void returnToMainMenu();

    /** @brief Load texture and create StartScreen sprite
      * @return Void.
      */ 
    sf::Sprite getGameOverScreenSprite();
};