#include <gameObjects/BlackCat.h>

/**  @brief The BlackCat constructor.
  *  Calls initializeCritter() to set attributes of the 
  *  BlackCat object
  */

BlackCat::BlackCat(int id, Waypoint* starting_waypoint) {
  this->id = id;
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

/**  Initialization specific to a BlackCat object
  */
void BlackCat::initializeCritter(const std::vector<Animation>& animations) {
  // Attributes for a white cat
  this->hit_points = 2;
  this->steal_coins = 4;
  this->player_reward = 5;
  this->type = Critter::CritterType::BLACK_CAT;
  this->speed = 20.0f;
  this->level = 1;
  this->animation_index = this->getMovementDirection();   

  // Set BlackCat texture
  TextureManager& t_manager = TextureManager::getInstance();
  this->sprite.setTexture(t_manager.loadTexture("resources/images/critters/BlackCatSpriteSheet.png"));

  /* Set up the initial animation */
  // Note, pixels are hardcoded for now for the frame size
  this->animation_handler.frame_size = sf::IntRect(0, 0, 32, 32); 

  //Add animations set in the constructor to handler
  for (auto animation : animations) {
    this->animation_handler.addAnimation(animation);
  }
  this->animation_handler.update(0.0f);   //Initial delta_time is 0
}

//Controlling the cat with Arrow Keys
void BlackCat::controlCat(sf::Keyboard::Key arrowKey) {
	if(arrowKey == sf::Keyboard::Up) {
		this->updatePosition(0, -2);
		this->animation_index = 3;
	}
	if(arrowKey == sf::Keyboard::Right) {
		this->updatePosition(+2, 0);
		this->animation_index = 2;
	}
	if(arrowKey == sf::Keyboard::Down) {
		this->updatePosition(0, +2);
		this->animation_index = 0;
	}
	if(arrowKey == sf::Keyboard::Left) {
		this->updatePosition(-2, 0);
		this->animation_index = 1;
	}
}