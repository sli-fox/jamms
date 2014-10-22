#include <gameObjects/Critter.h>

int Critter::getHitPoints() const {
  return hit_points;
}
void Critter::setHitPoints(int points){
  this->hit_points = points;
}
int Critter::getStealStrength() const {
  return steal_strength;
} 
int Critter::getPlayerReward() const {
  return player_reward;
} 
float Critter::getSpeed() const {
  return speed;
} 
int Critter::getLevel() const {
  return level;
}

void Critter::draw(sf::RenderWindow& game_window, float delta_time) {
  // Change the animation to reflect the current one
  this->animation_handler.changeAnimation(this->animation_index);
  
  // Update the animation
  this->animation_handler.update(delta_time);
       sf::IntRect r1(0, 0, 32, 32);
       //std::cout << this->animation_handler.bounding_rect.height;
  // Set texture bounds for sprite
  //this->sprite.setTextureRect(this->animation_handler.bounding_rect);
  this->sprite.setTextureRect(r1);
         std::cout << this->animation_handler.bounding_rect.height;


  //Draw the sprite
  game_window.draw(this->sprite);
}