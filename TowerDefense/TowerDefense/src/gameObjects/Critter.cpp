#include <gameObjects/Critter.h>

int Critter::getId() const {
  return id;
}
int Critter::getHitPoints() const {
  return hit_points;
}
void Critter::setHitPoints(int points){
  this->hit_points = points;
}
int Critter::getCoinsStrength() const {
  return steal_coins;
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

sf::Vector2f Critter::getPosition() const {
  return position;
}

Waypoint* Critter::getCurrentWaypoint() const {
  return current_waypoint;
}

void Critter::setCurrentWaypoint(Waypoint* waypoint) {
  this->current_waypoint = waypoint;
}

void Critter::setAnimationIndex(unsigned int index) {
  this->animation_index = index;
}


bool Critter::isAtNextWaypoint() {
  if (sf::Vector2f(int(position.x), int(position.y)) == current_waypoint->next_waypoint->position) {
    return true;
  }
  return false;
}


void Critter::updatePosition(float x, float y) {
  this->position.x += x; 
  this->position.y += y;
}

Critter::MovementDirection Critter::getMovementDirection() {
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

std::string Critter::getCritterSpecs() {
	//Since we can't cout an enum in C++, we need this Array system as a workaround (optional, but prettier at output)
	char *CritterTypeA[] = { "BLACK_CAT", "WHITE_CAT" };
	std::stringstream output;
	output << "CRITTER SPECIFICATIONS:" << std::endl;
	output << "Hit Points: " << this->hit_points << std::endl;
	output << "Type: " << CritterTypeA[this->type] << std::endl;
	output << "Steal Coins: " << this->steal_coins << std::endl;
	output << "Steal Lives: " << this->STEAL_LIVES << std::endl;
	output << "Player Reward: " << this->player_reward << std::endl;
	output << "Speed: " << this->speed << std::endl;

	return output.str();
}

//Controlling the cat with Arrow Keys
void Critter::controlCat(sf::Keyboard::Key arrowKey) {
	if(arrowKey == sf::Keyboard::Up) {
		if(this->getPosition().y > 0) {
			this->updatePosition(0, -2);
			this->animation_index = 3;
		}
	}
	if(arrowKey == sf::Keyboard::Right) {
		if(this->getPosition().x < Game::map.getMapWidth()*32) {
			this->updatePosition(+2, 0);
			this->animation_index = 2;
		}
	}
	if(arrowKey == sf::Keyboard::Down) {
		if(this->getPosition().y < Game::map.getMapHeight()*32) {
			this->updatePosition(0, +2);
			this->animation_index = 0;
		}
	}
	if(arrowKey == sf::Keyboard::Left) {
		if(this->getPosition().x > 0) {
			this->updatePosition(-2, 0);
			this->animation_index = 1;
		}
	}
}

void Critter::draw(sf::RenderWindow& game_window, float delta_time) {
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