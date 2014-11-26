#include <gameObjects/Critter.h>

Critter::Critter(){
	speedModifier = 1.0;
}

Critter::~Critter(){

}

int Critter::getId() const {
  return id;
}
int Critter::getHitPoints() const {
  return hit_points;
}
void Critter::setHitPoints(int points){
  this->hit_points = points;
}
int Critter::getStealPointsStrength() const {
  return steal_points;
} 
int Critter::getPlayerReward() const {
  return player_reward;
} 
float Critter::getSpeed() const {
	return speed * speedModifier;
}
void Critter::setSpeed(float speed) {
	this->speed = speed;
}
int Critter::getLevel() const {
  return level;
}
bool Critter::getSpecialEffectApplied() const {
	return this->specialEffectApplied;
}
void Critter::setSpecialEffectApplied(bool specialEffectsApplied) {
	this->specialEffectApplied = specialEffectsApplied;
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

void Critter::inflictDamage(int damage) {
	this->hit_points = (this->hit_points - damage <= 0 ? 0 : this->hit_points - damage);
}

bool Critter::isAtNextWaypoint() {
  if (sf::Vector2f(int(position.x), int(position.y)) == current_waypoint->next_waypoint->position) {
    return true;
  }
  return false;
}

void Critter::reduceSpeed(float speed) {
	this->speed = (this->speed - speed >= 10.0f ? this->speed - speed : 10.0f);
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
	output << "Critter Id: " << this->id << std::endl;
	output << "Current Health: " << this->getHitPoints() << std::endl;
	output << "Max Health: " << this->max_health << std::endl;
	output << "Type: " << CritterTypeA[this->type] << std::endl;
	output << "Steal Coins: " << this->steal_points << std::endl;
	output << "Player Reward: " << this->player_reward << std::endl;
	output << "Speed: " << this->speed << std::endl;

	return output.str();
}

//Controlling the cat with Arrow Keys
void Critter::controlCat(sf::Keyboard::Key arrowKey) {
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

void Critter::addEffect(CritterEffect effect){
	bool effectApplied = false;
	std::list<CritterEffect>::iterator it;
	for(it = effectList.begin() ; it != effectList.end() ; ++it){
		if(it->isEqual(effect)){
			it->addStacks(effect.getStacks());
			effectApplied = true;
			break;
		}
	}
	if(!effectApplied)
		effectList.push_back(effect);
}

void Critter::inflictEffects(){
	if(!effectList.empty()){
		std::list<CritterEffect>::iterator it = effectList.begin();
		speedModifier = 1.0;
		while(it != effectList.end()){
			it->tick();
			if(it->applyEffect()){
				if(it->getStacks() < 0){
					effectList.erase(it++);
					continue;
				}
				/*std::cout << "critter ID: " << this->getId()
				<< ", Num of effects: " << int(effectList.size()) 
				<< ", Num of stacks: " << it->getStacks() << std::endl;
				*/
				inflictDamage(it->getDamage());
			}
			if(it->getSpeedModifer() < speedModifier)
				speedModifier = it->getSpeedModifer();
			++it;
		}
	}
}