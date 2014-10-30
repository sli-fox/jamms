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
#include <gameStates/GameStatePlay.h>
#include <managers/GameObjectManager.h>
#include <gameObjects/WhiteCat.h>
#include <utils/Waypoint.h>
#include <iostream>
#include <Map.h>

/** @brief Game state that represents the gameplay.
 */
class GameStatePlay : public GameState {
  public:
    WhiteCat* mew; 

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

     /** @brief Get starting waypoint 
      *  @return Vector containing Waypoint pointers.
      */
    Waypoint* getStartingWaypoint() {
      return &current_waypoints[0];
    }


   private:
     /** @brief Camera view for the gameplay displayed to the window.
      */
     sf::View _gameView;

     /** @brief Camera view for the HUD displayed to the window.
      */
     sf::View _guiView;

     std::vector<Waypoint> current_waypoints;

     static GameObjectManager _game_object_manager;
	   
     static Map map;

     /** @brief Add waypoints 
      *  @return Vector containing Waypoint pointers.
      */
     std::vector<Waypoint> addWaypoints(std::vector<sf::Vector2f> path_points);

     /**  @brief Draw all waypoints
      *   @return Void.
      */
     void drawWaypoints(std::vector<Waypoint> waypoints, sf::RenderWindow& game_window);
	 
     void mapCommandLibrary(const int tileX, const int tileY, sf::Keyboard::Key thisKey);

};