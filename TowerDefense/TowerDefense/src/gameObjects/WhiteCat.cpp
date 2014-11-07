#include <gameObjects/WhiteCat.h>

/**  @brief The WhiteCat constructor.
  *  Calls initializeCritter() to set attributes of the 
  *  WhiteCat object
  */

WhiteCat::WhiteCat(int id, Waypoint* starting_waypoint) {
  this->id = id;
  max_health = 15;
  this->current_waypoint = starting_waypoint;
  
  //Set starting position
  this->position = current_waypoint->position;
  
  // Set up animation
  Animation animation1(0, 2, 0.5f), animation2(0, 2, 0.5f), animation3(0, 2, 0.5f), animation4(0, 2, 0.5f);
  std::vector<Animation> animations;
  animations.push_back(animation1);
  animations.push_back(animation2);
  animations.push_back(animation3);
  animations.push_back(animation4);
  initializeCritter(animations);
}

/**  Initialization specific to a WhiteCat object
  */
void WhiteCat::initializeCritter(const std::vector<Animation>& animations) {
  // Attributes for a white cat
  this->isActive = false;
  this->hasSpawned = false;
  this->isAtEndTile = false;
  this->hit_points = this->max_health;
  this->steal_points = 4;
  this->player_reward = 5;
  this->type = Critter::CritterType::WHITE_CAT;
  this->speed = 10.0f;
  this->level = 1;
  this->animation_index = this->getMovementDirection();   

  // Set WhiteCat texture
  TextureManager& t_manager = TextureManager::getInstance();
  this->sprite.setTexture(t_manager.loadTexture("resources/images/critters/WhiteCatSpriteSheet.png"));

  /* Set up the initial animation */
  // Note, pixels are hardcoded for now for the frame size
  this->animation_handler.frame_size = sf::IntRect(0, 0, 32, 32); 

  //Add animations set in the constructor to handler
  for (auto animation : animations) {
    this->animation_handler.addAnimation(animation);
  }
  this->animation_handler.update(0.0f);   //Initial delta_time is 0
}