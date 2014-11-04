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
#include <SFML/Graphics/Transformable.hpp>
#include <gameStates/GameState.h>
#include <managers/GameObjectManager.h>
#include <gameObjects/WhiteCat.h>
#include <gameObjects/BlackCat.h>
#include <utils/Waypoint.h>
#include <iostream>
#include <stack>
#include <Map.h>
#include <managers/TowerManager.h>
#include <managers/CritterWave.h>


/** @brief Game state that represents the gameplay.
 */
class GameStatePlay : public GameState {
  public:
    WhiteCat* mew;
    BlackCat* blacky;

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
    Waypoint* getStartingWaypoint();

    CritterWave* getCurrentCritterWave();

   private:

<<<<<<< HEAD
	  sf::Vector2i  localPosition;
	  int tileX, tileY;
	  std::map<string,GameObject> buttonMap;
	  bool returnToMenu;
	  sf::CircleShape range;
	  Tower::TowerType towerSelector;
	  sf::Font font;

	  sf::Vector2i  localPosition;
	  int tileX, tileY;
	  GameObject mapBackdrop;
	  std::map<string,GameObject> buttonMap;
	  bool returnToMenu;
	  sf::CircleShape range;
	  Tower::TowerType towerSelector;
	  sf::Font font;
	  sf::Text towerSpecs;
	  sf::Text critterSpecs;
	  sf::Text playerSpecs;
	
     /** @brief Camera view for the gameplay displayed to the window.
      */
     sf::View _gameView;

     /** @brief Camera view for the HUD displayed to the window.
      */
     sf::View _guiView;

     CritterWave* current_wave; 
     std::stack<CritterWave*> wave_levels;

     std::vector<Waypoint> current_waypoints;
	 
     static GameObjectManager _game_object_manager;
     static TowerManager& tower_manager;

     /** @brief Add waypoints 
      *  @return Vector containing Waypoint pointers.
      */
     std::vector<Waypoint> addWaypoints(std::vector<sf::Vector2f> path_points);

     /** @brief Create waypoint vector from the map's path 
      *  @return Vector containing positions.
      */
     std::vector<sf::Vector2f> getWaypointsFromMapPath();

     /**  @brief Draw all waypoints
      *   @return Void.
      */
     void drawWaypoints(std::vector<Waypoint> waypoints, sf::RenderWindow& game_window);
	 
     void moveCritter(Critter* critter, const float delta_time);
	   void initializeButtonMap();
	   void buttonCommandLibrary();
     void towerCommandLibrary(const int tileX, const int tileY);
     bool checkIfAtEndTile(Critter* critter);

     /**  @brief Initialize stack containing preset levels for critter waves
      *   @return Void.
      */
     void setCritterWaveLevels();

     void handleCritterActivationWithinWave();

};