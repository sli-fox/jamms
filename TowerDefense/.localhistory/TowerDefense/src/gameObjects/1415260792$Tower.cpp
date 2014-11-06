#pragma once
#include <GameObjects/Tower.h>

Tower::Tower() {
	this->_upgrade_level = Tower::UpgradeLevel::Upgrade0;
	this->_is_firing = false;
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
	_range_shape.setOutlineColor(sf::Color(100, 100, 100));
	_range_shape.setOrigin(float(this->getRange()*32), float(this->getRange()*32));
}

sf::CircleShape Tower::getRangeShape() const {
	return _range_shape;
}

bool Tower::canAttack(Critter* crit) {
	if(this == NULL) return false;

	this->time = this->clock.getElapsedTime();

	int distX = int(crit->getPosition().x - this->getPosition().x-16);
	int distY = int(crit->getPosition().y - this->getPosition().y-16);
	int pythagore = static_cast<int> (pow(static_cast<double> (distX), 2))
	+ static_cast<int> (pow(static_cast<double> (distY), 2));

	if(sqrt(pythagore) <= this->getRangeShape().getRadius()
		&& time.asSeconds()*this->getRateOfFire() >= 1
		&& this->_target == NULL) {
		_target = crit;
		clock.restart();
		return true;
	}
	return false;
}

void Tower::update(Critter* crit) {
	std::cout << white << "Time: " << time.asSeconds() << " seconds" << std::endl;
	std::cout << white << "WOUF WOUF!" << std::endl;
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