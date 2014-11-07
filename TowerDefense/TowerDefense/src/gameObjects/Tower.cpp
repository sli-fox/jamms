#pragma once
#include <GameObjects/Tower.h>

Tower::Tower() {
	this->_upgrade_level = Tower::UpgradeLevel::Upgrade0;
	this->_target = NULL;
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
int Tower::getBuyCost() const {
	return _buy_cost;
}
int Tower::getSellCost() const {
	return _sell_cost;
}
int Tower::getUpgradeCost() const {
	return _upgrade_cost;
}
Critter* Tower::getTarget() const {
	return _target;
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
void Tower::setTarget(Critter* crit) {
	this->_target = crit;
}

void Tower::setRangeShape(Tower::Range range) {
	_range_shape.setRadius(float((range+1) * 32));
	_range_shape.setFillColor(sf::Color::Transparent);
	_range_shape.setOutlineThickness(2);
	_range_shape.setOutlineColor(sf::Color::Red);
	_range_shape.setOrigin(float(this->getRange()*32), float(this->getRange()*32));
}

sf::CircleShape Tower::getRangeShape() const {
	return _range_shape;
}

/**
  * @brief Determines whether tower can attack a critter based on whether the critter falls within its range while taking into account the tower's rate of fire delay
  * @return bool
  */
bool Tower::canAttack(Critter* critter) {
	if(this == NULL)
		return false;

	this->time = this->clock.getElapsedTime();
	
	if(this->_target != NULL && this->_target->getId() < critter->getId())
		_target = critter;

	if(this->circleToCircleIntersection(critter) && time.asSeconds()*this->getRateOfFire() >= 1 && this->_target == NULL) {
		_target = critter;
		clock.restart();
		return true;
	}
	this->_target = NULL;
	return false;
}

void Tower::attack() {
	std::cout << yellow << "WOUF WOUF! Scared cat " << this->_target->getId() << std::endl;
    this->_target->inflictDamage(this->getPower());
	std::cout << yellow << "Cat " << this->_target->getId() << " now has " << this->_target->getHitPoints() << " HP" << std::endl;
}

void Tower::update() {
	std::cout << "TOWER UPDATED!" << std::endl;
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