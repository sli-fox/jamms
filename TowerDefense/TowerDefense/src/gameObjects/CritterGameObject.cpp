#include <gameObjects/CritterGameObject.h>

void CritterGameObject::setAnimationIndex(unsigned int index) {
  this->animation_index = index;
}

Waypoint* CritterGameObject::getCurrentWaypoint() const {
  return current_waypoint;
}

void CritterGameObject::setCurrentWaypoint(Waypoint* waypoint) {
  this->current_waypoint = waypoint;
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

bool CritterGameObject::isAtNextWaypoint() {
  if (sf::Vector2f(int(position.x), int(position.y)) == current_waypoint->next_waypoint->position) {
    return true;
  }
  return false;
}

CritterGameObject::MovementDirection CritterGameObject::getMovementDirection() {
  sf::Vector2f start_position = this->current_waypoint->position;
  sf::Vector2f end_position = this->current_waypoint->next_waypoint->position;
  if (start_position.x == end_position.x
      && start_position.y - end_position.y > 0)
      return UP;
  if (start_position.x == end_position.x
      && start_position.y - end_position.y < 0)
      return DOWN;
  if (start_position.y == end_position.y
    && start_position.x - end_position.x > 0)
      return LEFT;
  if (start_position.y == end_position.y
    && start_position.x - end_position.x < 0)
      return RIGHT;
}

void CritterGameObject::updatePosition(float x, float y) {
  this->position.x += x; 
  this->position.y += y;
}

//Controlling the cat with Arrow Keys
void CritterGameObject::controlCat(sf::Keyboard::Key arrowKey) {
	if(arrowKey == sf::Keyboard::Up) {
		if(this->getPosition().second > (0 + this->getSpriteSize().second / 3.0)) {
			this->updatePosition(0, -2);
			this->animation_index = 3;
		}
	}
	if(arrowKey == sf::Keyboard::Right) {
		if(this->getPosition().first < (Game::map.getMapWidth()*32 - this->getSpriteSize().first / 2.0)) {
			this->updatePosition(+2, 0);
			this->animation_index = 2;
		}
	}
	if(arrowKey == sf::Keyboard::Down) {
		if(this->getPosition().second < (Game::map.getMapHeight()*32 - this->getSpriteSize().second / 2.0)) {
			this->updatePosition(0, +2);
			this->animation_index = 0;
		}
	}
	if(arrowKey == sf::Keyboard::Left) {
		if(this->getPosition().first > (0 + this->getSpriteSize().first / 2.0)) {
			this->updatePosition(-2, 0);
			this->animation_index = 1;
		}
	}
}
