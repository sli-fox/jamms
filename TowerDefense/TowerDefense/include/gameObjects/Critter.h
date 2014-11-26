/** @file Critter.h
*  @brief Representation of critter object.
*
*  This is the abstract representation of the critter object.
*
*  @author Stephanie Li
*/

#pragma once
#include <gameObjects/CritterGameObject.h>
#include <utils/AnimationHandler.h>
#include <utils/Waypoint.h>
#include <gameObjects/ISubject.h>

/** @brief Abstract base class of all Critters
*  Critter defines the attributes, accessors, and update function
*  for its subclass instances. 
*/
class Critter : public CritterGameObject, public ISubject {
public:
  enum MovementDirection { DOWN, LEFT, RIGHT, UP };
  enum CritterType { BLACK_CAT, WHITE_CAT };

  void controlCat(sf::Keyboard::Key arrowKey);

  bool isActive;
  bool hasSpawned;
  bool isAtEndTile;
  Critter* next_critter;

  Critter() {};
  virtual ~Critter() {};

  int getId() const;
  int getHitPoints() const; 
  void setHitPoints(int points);
  int getStealPointsStrength() const; 
  int getPlayerReward() const; 
  float getSpeed() const;
  void setSpeed(float speed);
  void reduceSpeed(float speed);
  int getLevel() const;
  Waypoint* getCurrentWaypoint() const;
  void setCurrentWaypoint(Waypoint* waypoint);
  bool getSpecialEffectApplied() const;
  void setSpecialEffectApplied(bool specialEffectApplied);


  void inflictDamage(int dmg);

  MovementDirection getMovementDirection();

  void updatePosition(float x, float y);

  bool isAtNextWaypoint();


  std::string getCritterSpecs();

protected:
  Waypoint* current_waypoint;

  CritterType type;
  int id;
  int max_health;

  /** @brief Pure virtualized initialization function for Critter.
  *   @return Void.
  */
  virtual void initializeCritter(const std::vector<Animation>& animations) = 0;

  /** @brief Health of the Critter.
  */
  int hit_points;

  /** @brief Rate at which the critter can steal points from the player.
  */
  int steal_points;

  /** @brief Rate at which the critter can steal lives from the player.
  */
  static const int STEAL_LIVES = 1;

  /** @brief Coin reward for the player when the Critter is killed 
  */
  int player_reward;

  /** @brief Critter movement speed 
  */
  float speed;

  /** @brief Difficulty level as part of a wave
  */
  int level;

  /**
  * @brief
  */
  bool specialEffectApplied;
};