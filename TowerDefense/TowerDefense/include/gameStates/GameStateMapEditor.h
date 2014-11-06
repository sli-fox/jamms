/** @file GameStateMapEditor.h
 *  @brief File containing the GameStateMapEditor class.
 *
 *  The purpose of this file is to implement a class that
 *  is a concrete game state representing the "map editor" state. 
 *
 *  @author Jeremy Melnyk
 */

#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <iostream>
#include <gameStates/GameState.h>
#include <gameStates/GameStatePlay.h>
#include "dirent.h"

/** @brief Game state that represents the gameplay.
 */
class GameStateMapEditor : public GameState {
  public:

    /** @brief Constructor that takes in a pointer to the Game
     *  that created them.
     *  @param game Pointer to game.
     */
	  
	GameStateMapEditor(Game* game);
    
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
	   sf::Vector2i  localPosition;
	   int tileX, tileY, mapX, mapY;
	   Tile::TYPE tileSelector;
	   GameObject mapBackdrop;
	   std::map<string,GameObject> buttonMap;
	   bool returnToMenu, pauseSave, pauseLoad;
	   string userInput;
	   sf::Text displayXsize, displayYsize, systemOutput, userInputDisplay;
	   sf::Font font;
	  vector<string> mapFiles;
		 
     /** @brief Camera view for the gameplay displayed to the window.
      */
     sf::View _gameView;

     /** @brief Camera view for the HUD displayed to the window.
      */
     sf::View _guiView;

	 const vector<string> getFilesInDir(const string dir);
	 void initializeButtonMap();
	 void buttonCommandLibrary();
     void mapEditorCommandLibrary();
};