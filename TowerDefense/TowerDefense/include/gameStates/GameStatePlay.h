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
#include <gameStates/GameStateGameOver.h>
#include <gameStates/GameStateWin.h>
#include <managers/GameObjectManager.h>
#include <gameObjects/WhiteCat.h>
#include <gameObjects/BlackCat.h>
#include <utils/Waypoint.h>
#include <algorithm>
#include <iostream>
#include <thread>
#include <Map.h>
#include <managers/TowerManager.h>
#include <managers/CritterWave.h>
#include <list>


/** @brief Game state that represents the gameplay.
 */
class GameStatePlay : public GameState {
  public:
    WhiteCat* mew;
    BlackCat* blacky;
    int delay_count;
    Critter* last_activated_critter;
    bool firstStart;
    bool show_waypoints;
    bool endOfWaves;
    
    std::thread drawThread;
    virtual void runThreads();

    /** @brief Constructor that takes in a pointer to the Game
     *  that created them.
     *  @param game Pointer to game.
     */
    GameStatePlay(Game* game);

    ~GameStatePlay() {
      if (drawThread.joinable())
        drawThread.join();
    }

    void handleGameOver();
    
	  void registerObserver(Tower* tower);

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
	  sf::Vector2i  localPosition;
	  int tileX, tileY;
	  GameObject mapBackdrop, interfaceBackdrop;
	  std::map<string,GameObject> buttonMap;
	  bool returnToMenu;
	  sf::CircleShape range;
	  std::string towerSelector;
	  Tower* fieldTowerSelector;
	  sf::Font font;
	  //sf::Text upgradeTowerSpecs;
	  sf::Text waveSpecs, nextWaveSpecs, playerSpecs, towerSpecs, critterSpecs, buttonSpecs;
	  sf::Text nearestTower;
	  sf::Text nearestEnd;
	  sf::Text strongest;
	  sf::Text weakest;
	  sf::Text mostH;
	  sf::Text leastH;
	  sf::Text slowest;
	  sf::Text fastest;
	  sf::Text mostCoins;
	  std::map<int,sf::Text> critterHealth;
	  std::map<int,sf::Clock> healthClock;
	  sf::Time healthTime;

	  std::map<int,sf::Text> effectDamage;
	  std::map<int,sf::Clock> effectDamageClock;
	  sf::Time effectDamageTime;
	
     /** @brief Camera view for the gameplay displayed to the window.
      */
     sf::View _gameView;

     /** @brief Camera view for the HUD displayed to the window.
      */
     sf::View _guiView;

     CritterWave* current_wave; 
     std::vector<CritterWave*> wave_levels;

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
     void moveActivatedCritters(const float delta_time);
     void moveCritter(Critter* critter, const float delta_time);
	   void initializeButtonMap();
	   void buttonCommandLibrary();
     void towerCommandLibrary(const int tileX, const int tileY);
     bool checkIfAtEndTile(Critter* critter);

     void handleCritterRemovalFromWave();
     void handleCritterWaveLevelSwitching();
     void setCritterWaveLevels(Waypoint* starting_waypoint);

	 static std::string getTower1ButtonSpecs();
	 static std::string getTower2ButtonSpecs();
	 static std::string getTower3ButtonSpecs();
	 static std::string getPauseButtonSpecs();
	 static std::string getUnPauseButtonSpecs();
	 static std::string getReturnToEditorButtonSpecs();
	 static std::string getStartWaveButtonSpecs();

};
