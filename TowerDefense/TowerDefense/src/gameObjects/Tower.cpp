#pragma once
#include <GameObjects/Tower.h>

Tower::Tower() {
	this->_upgrade_level = Tower::UpgradeLevel::Upgrade0;
	this->time = clock.getElapsedTime();
}

//ACCESSORS
int Tower::getID() const {
	return _id;
}
std::string Tower::getName() const {
	return _name;
}
Tower::TowerType Tower::getType() const {
	return _type;
}
Tower::UpgradeLevel Tower::getUpgradeLevel() const {
	return _upgrade_level;
}
int Tower::getPower() const {
	return _power;
}
Tower::Range Tower::getRange() const {
	return _range;
}
Tower::RateOfFire Tower::getRateOfFire() const {
	return _rate_of_fire;
}
Tower::SpecialEffect Tower::getSpecialEffet() const {
	return _special_effect;
}
int Tower::getSellCost() const {
	return _sell_cost;
}
int Tower::getUpgradeCost() const {
	return _upgrade_cost;
}

//MUTATORS
void Tower::setID(int _id) {
	this->_id = _id;
}
void Tower::setType(Tower::TowerType _tower_type) {
	this->_type = _tower_type;
}
void Tower::setUpgradeLevel(Tower::UpgradeLevel _upgrade_level) {
	this->_upgrade_level = _upgrade_level;
}
void Tower::setPower(int _power) {
	this->_power = _power;
}
void Tower::setRange(Tower::Range _range) {
	this->_range = _range;
}
void Tower::setRateOfFire(Tower::RateOfFire _rate_of_fire) {
	this->_rate_of_fire = _rate_of_fire;
}
void Tower::setSpecialEffet(Tower::SpecialEffect _special_effect) {
	this->_special_effect = _special_effect;
}
void Tower::setSellCost(int _sell_cost) {
	this->_sell_cost = _sell_cost;
}
void Tower::setUpgradeCost(int _upgrade_cost) {
	this->_upgrade_cost = _upgrade_cost;
}

void Tower::setRangeShape(Tower::Range range) {
	_range_shape.setRadius(float((range+1) * 32));
	_range_shape.setFillColor(sf::Color::Transparent);
	_range_shape.setOutlineThickness(2);
	_range_shape.setOutlineColor(sf::Color(100, 100, 100));
	_range_shape.setOrigin(float(this->getRange()*32), float(this->getRange()*32));
}

sf::CircleShape Tower::getRangeShape() const {
	return _range_shape;
}

/**
  * @brief Determines whether the tower can deliver another attack based on its rate of fire
  * @return bool
  */
bool Tower::canAttack() {
	this->time = this->clock.getElapsedTime();

	if(time.asSeconds() * this->getRateOfFire() >= 1) {
		clock.restart();
		return true;
	}
	return false;
}

/**
  * @brief Inserts critter in queue to be attacked by tower
  * @return void
  */
void Tower::insertCritterInQueue(Critter* critter) {
	//if(this->_critters_in_range.find(
	this->_critters_in_range.insert(critter);
}

/**
  * @brief Removes frontmost critter from the queue
  * @return void
  */
void Tower::removeCritterInFront(){
	if(!this->_critters_in_range.empty())
		if(!this->critterIsWithinRange(*this->_critters_in_range.begin())){
			cout << "CRITTERS IN SET: " << int(_critters_in_range.size()) << endl;
			this->_critters_in_range.erase(this->_critters_in_range.begin());
			cout << "CRITTERS IN SET: " << int(_critters_in_range.size()) << endl;
		}
}

/**
  * @brief Determines whether critter falls within tower range
  * @return bool
  */
bool Tower::critterIsWithinRange(Critter* critter) {
	return this->circleToCircleIntersection(critter);
}

/**
  * @brief Tower attacks a critter in range. Attack aftermath may be critter death, player gaining points, etc.
  * @return void
  */
void Tower::attack() {
	
	//this->spawnProjectile(this->getPosition(), this->_power, this->_rate_of_fire, critter) {
		//Projectile* projectile = new Projectile(this->getPosition(), this->_power);
		//projectile->findCollisionPath(critter);
		//projectile->animate() {
		//  this->rotate(angle(_collision_path.x, _collision_path.y)
		//	this->move(_collision_path);	
		//}
	//}
	
	if(!_critters_in_range.empty()){
		Critter* thisCritter = *_critters_in_range.begin();

		if(thisCritter->getHitPoints() > 0) {
			std::cout << white << "Time: " << time.asSeconds() << " seconds" << std::endl;
			std::cout << white << "WOUF WOUF!" << std::endl;
	
			std::cout << white << "Critter " << thisCritter->getId() << " Hit!" << std::endl; 
			std::cout << white << "Critter took " << this->_power << " damage from " << this->_name << std::endl;
			thisCritter->setHitPoints(thisCritter->getHitPoints() - this->_power);
		}
		else if(thisCritter->getHitPoints() <= 0) {
			thisCritter->isDefeated = true;
			std::cout << white << "Time: " << time.asSeconds() << " seconds" << std::endl;
			std::cout << white << "WOUF WOUF!" << std::endl;
	
			std::cout << white << "CRITTER DEFEATED!" << std::endl;
			std::cout << white << "Awarded " << thisCritter->getPlayerReward() << " points!" << std::endl;
			Game::player.gainPoints(thisCritter->getPlayerReward());

			int cash = 5; //should have the cash reward be specific to a wave. so wave 1 gives you 5 cash per kill, wave 2 gives you 10 cash etc etc. so we'd use CritterWave::getWave().coinReward
			std::cout << white << "Gained " << cash << " coins!" << std::endl;
			Game::player.earnCash(cash);
		}
	}
}

std::string Tower::getTowerSpecs() {
	//Since we can't cout an enum in C++, we need this Array system as a workaround (optional, but prettier at output)
	char *TowerTypeA[] = { "ShihTzu", "Dalmatian", "Bulldog" };
	char *UpgradeLevelA[] = { "Upgrade0", "Upgrade1", "Upgrade2" };
	char *RangeA[] = { "Small", "Medium", "Large" };
	char *RateOfFireA[] = { "Slow", "Normal", "Fast" };
	char *SpecialEffectA[] = { "None", "Slowing", "Burning", "Freezing" };
	std::stringstream output;
	output << "TOWER SPECIFICATIONS:" << std::endl;
	output << "Name: " << this->_name << std::endl;
	output << "Type: " << TowerTypeA[this->_type] << std::endl;
	output << "Upgrade: " << UpgradeLevelA[this->_upgrade_level] << std::endl;
	output << "Power: " << this->_power << std::endl;
	output << "Range:  " << RangeA[this->_range-1] << std::endl;
	output << "Fire Rate: " << RateOfFireA[this->_rate_of_fire-1] << std::endl;
	output << "Special Effect: " << SpecialEffectA[this->_special_effect] << std::endl;
	output << "Upgrade Cost: " << this->_upgrade_cost << " coins" << std::endl;
	output << "Sell Cost: " << this->_sell_cost << " coins" << std::endl;

	return output.str();
}

/**
  * @brief Overrides method to apply to tower range sf::CircleShape object
  * @return bool
  */
bool Tower::circleToCircleIntersection(GameObject* game_object){
	float radius = this->_range_shape.getRadius();

	sf::Vector2f distance = this->getSpriteCenter() - game_object->getSpriteCenter();
	
	return sqrt(distance.x * distance.x + distance.y * distance.y) <= radius;
}