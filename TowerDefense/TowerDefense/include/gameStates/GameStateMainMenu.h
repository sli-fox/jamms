/** @file GameStateMainMenu.h
 *  @brief File containing the GameStateMainMenu class.
 *
 *  The purpose of this file is to implement a class that
 *  is a concrete game state representing the "Main Menu" state. 
 *
 *  @author Stephanie Li
 */

#pragma once
#include <SFML/Graphics.hpp>
#include <gameStates/GameState.h>
#include <gameStates/GameStatePlay.h>
#include <gameStates/GameStateEditor.h>
#include <managers/TextureManager.h>
#include <views/MainMenu.h>

/** @brief Game state that represents the game start,
 *  including the main game menu.
 */
class GameStateMainMenu : public GameState {
  public:
    /** @brief Constructor that takes in a pointer to the Game
     *  that created them.
     *  @param game Pointer to game.
     */
    GameStateMainMenu(Game* game);

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
    /** @brief Camera view for the GameState displayed to the window.
    */
    sf::View _view;

    /** @brief The user selected action on the menu.
    */
    Menu::MenuAction selected_action;

    /** @brief Function that transitions to the GameStatePlay state. 
    *   @return Void.
    */
    void loadGame();

    /** @brief Perform the correct action given the user's selection.
      * @return Void.
      */
    void handleSelectedAction();

};