#include <gameObjects/WhiteCat.h>

/**  @brief The WhiteCat constructor.
  *  Calls initializeCritter() to set attributes of the 
  *  WhiteCat object
  */
WhiteCat::WhiteCat() {
  // Set up animation
  Animation animation1(0, 2, 0.5f), animation2(0, 3, 0.5f);
  std::vector<Animation> animations;
  animations.push_back(animation1);
  animations.push_back(animation2);
  initializeCritter(animations);
}

/**  Initialization specific to a WhiteCat object
  */
void WhiteCat::initializeCritter(const std::vector<Animation>& animations) {
  // Attributes for a white cat
  this->hit_points = 2;
  this->steal_strength = 4;
  this->player_reward = 5;
  this->speed = 2.0f;
  this->level = 1;
  this->animation_index = 1;   // initialized to 1 for first line in sprite sheet

  // Set WhiteCat texture
  TextureManager& t_manager = TextureManager::getInstance();
  this->sprite.setTexture(t_manager.loadTexture("resources/images/WhiteCatSpriteSheet.png"));

  /* Set up the initial animation */
  // Note, pixels are hardcoded for now for the frame size
  this->animation_handler.frame_size = sf::IntRect(0, 0, 32, 32);
  
  //this->animation_handler.setCurrentAnimation(1); 

  //Add animations set in the constructor to handler
  for (auto animation : animations) {
    this->animation_handler.addAnimation(animation);
  }
  this->animation_handler.update(0.0f);   //Initial delta_time is 0
}


void WhiteCat::update() {

}