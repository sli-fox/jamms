/** @file GameStateEditor.h
 *  @brief File containing the GameStateEditor class.
 *
 *  The purpose of this file is to implement a class that
 *  is a concrete game state representing the "editor" state. 
 *
 *  @author Jeremy Melnyk
 */

#pragma once
#include <SFML/Graphics.hpp>
#include <gameStates/GameState.h>
#include <managers/GameObjectManager.h>
#include <iostream>
#include "EditorButtons.h"

/** @brief Game state that represents the editor.
 */
class GameStateEditor : public GameState {
  public:

    /** @brief Constructor that takes in a pointer to the Game
     *  that created them.
     *  @param game Pointer to game.
     */
    GameStateEditor(Game* game);
    
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

	void initializeInterface();
	void drawInterface(sf::RenderWindow& gameWindow);

   private:
     /** @brief Camera view for the editor displayed to the window.
      */
     sf::View _editorView;

     /** @brief Camera view for the HUD displayed to the window.
      */
     sf::View _guiView;
	 sf::Vector2i localPosition;
	 int tileX, tileY;
	 sf::Text testText;
	 sf::Text shownText;

	 void mapCommandLibrary(const int tileX, const int tileY);
};
