/** @file Critter.h
 *  @brief Representation of critter object.
 *
 *  This is the abstract representation of the critter object.
 *
 *  @author Stephanie Li
 */

#pragma once
#include <gameObjects/GameObject.h>
#include <utils/AnimationHandler.h>
#include <utils/Waypoint.h>

/** @brief Abstract base class of all Critters
 *  Critter defines the attributes, accessors, and update function
 *  for its subclass instances. 
 */
class Critter : public GameObject {
  public:
    enum MovementDirection { DOWN, LEFT, RIGHT, UP };
    enum CritterType { NONE, BLACK_CAT, WHITE_CAT };

   /** @brief Handles the animated object. 
     */
    AnimationHandler animation_handler;

    bool isActive;
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
    int getLevel() const;
    sf::Vector2f getPosition() const;
    Waypoint* getCurrentWaypoint() const;
    void setCurrentWaypoint(Waypoint* waypoint);
    void setAnimationIndex(unsigned int index);
  
  MovementDirection getMovementDirection();
  
  void updatePosition(float x, float y);

  bool isAtNextWaypoint();

  
  std::string getCritterSpecs();

  /** @brief Draw a Critter.
  *  @param game_window Reference to the window, passed in so that Critters
  *  don't need to know about the Game class.
  *  @param delta_time Elapsed time 
  *  @return Void.
  */
  void draw(sf::RenderWindow& game_window, float delta_time);

  protected:
    Waypoint* current_waypoint;

    CritterType type;
    int id;

    /** @brief Pure virtualized initialization function for Critter.
    *   @return Void.
    */
    virtual void initializeCritter(const std::vector<Animation>& animations) = 0;

    /** @brief Health of the Critter.
      */
    int hit_points;

    /** @brief Position of the Critter.
      */
    sf::Vector2f position;

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

    /** @brief Indicates which animation in a sprite sheet
     */
    int animation_index;
};