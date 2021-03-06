/** @file CritterGameObject.h
*  @brief File containing the CritterGameObject class.
*
*  The purpose of this file is to implement a class that
*  represents a displayed Critter in the application. 
*
*  @author Stephanie Li
*/

#pragma once
#include <gameObjects/GameObject.h>
#include <utils/AnimationHandler.h>
#include <utils/Waypoint.h>

/** @brief Creates a CritterGameObject.
*  CritterGameObject is a subclass of GameObject that separates 
*  GUI code specific to the Critter from the Critter model in the
*  application. 
*/
class CritterGameObject : public GameObject {
public:
  enum MovementDirection { DOWN, LEFT, RIGHT, UP };
  bool isActive;
  bool hasSpawned;
  bool isAtEndTile;

  /** @brief Handles the animated object. 
  */
  AnimationHandler animation_handler;

  CritterGameObject() {};
  virtual ~CritterGameObject() {};

  Waypoint* getCurrentWaypoint() const;
  void setCurrentWaypoint(Waypoint* waypoint);
  void setAnimationIndex(unsigned int index);

  /** @brief Draw a Critter.
  *  @param game_window Reference to the window, passed in so that Critters
  *  don't need to know about the Game class.
  *  @param delta_time Elapsed time 
  *  @return Void.
  */
  void draw(sf::RenderWindow& game_window, float delta_time);
  MovementDirection getMovementDirection();
  bool isAtNextWaypoint();
  void updatePosition(float x, float y);

  void controlCat(sf::Keyboard::Key arrowKey);


protected:
  Waypoint* current_waypoint;

  /** @brief Indicates which animation in a sprite sheet
  */
  int animation_index;
};