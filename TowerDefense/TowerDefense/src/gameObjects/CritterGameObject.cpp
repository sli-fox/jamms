#include <gameObjects/CritterGameObject.h>

void CritterGameObject::setAnimationIndex(unsigned int index) {
  this->animation_index = index;
}

void CritterGameObject::draw(sf::RenderWindow& game_window, float delta_time) {
  // Change the animation to reflect the current one
  this->animation_handler.changeAnimation(this->animation_index);
  
  // Update the animation
  this->animation_handler.update(delta_time);

  // Set texture bounds for sprite
  this->sprite.setTextureRect(this->animation_handler.bounding_rect);

  //Set position for drawn sprite
  sprite.setPosition(position);

  //Reset origin for drawn sprite
  sprite.setOrigin(16, 16);

  //Draw the sprite
  game_window.draw(this->sprite);
}