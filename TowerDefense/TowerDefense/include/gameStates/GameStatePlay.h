/** @file GameStatePlay.h
 *  @brief File containing the GameStateStart class.
 *
 *  The purpose of this file is to implement a class that
 *  is a concrete game state representing the "play" state. 
 *
 *  @author Stephanie Li
 */

#pragma once
#include <SFML/Graphics.hpp>
#include <gameStates/GameState.h>
#include <managers/GameObjectManager.h>
#include <gameObjects/WhiteCat.h>

/** @brief Game state that represents the gameplay.
 */
class GameStatePlay : public GameState {
  public:
    WhiteCat mew;

    /** @brief Constructor that takes in a pointer to the Game
     *  that created them.
     *  @param game Pointer to game.
     */
    GameStatePlay(Game* game);
    
    /** @brief Draws game to the render window. 
    *   @param delta_time Elapsed time during the game.
    *   @return Void.
    */
    virtual void draw(const float delta_time);
    
    /** @brief Updates game changes. 
    *   @param delta_time Elapsed time during the game.
    *   @return Void.
    */
    virtual void update(const float delta_time);
    
    /** @brief Handles player input. 
     *   @return Void.
     */
    virtual void handleInput();

   private:
     /** @brief Camera view for the gameplay displayed to the window.
      */
     sf::View _gameView;

     /** @brief Camera view for the HUD displayed to the window.
      */
     sf::View _guiView;

     static GameObjectManager _game_object_manager;
};