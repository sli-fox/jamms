#pragma once
#include <GameObjects/Tower.h>
#define _USE_MATH_DEFINES
#include <math.h>

int Tower::serial = 0;

Tower::Tower() {
	this->_upgrade_level = Tower::UpgradeLevel::Baby;
	this->_target = NULL;
	this->_strategy.reset(new NearestEndPointStrategy());
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
float Tower::getRange() const {
	return _range;
}

Tower::SpecialEffect Tower::getSpecialEffect() const {
	return _special_effect;
}
int Tower::getBuyCost() const {
	return _sell_cost;
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
void Tower::setName(std::string _name) {
	this->_name = _name;
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

void Tower::setRange(float _range) {
	this->_range = _range;
	this->setRangeShape(_range);
}

void Tower::setSpecialEffect(Tower::SpecialEffect _special_effect) {
	this->_special_effect = _special_effect;
}
void Tower::setSellCost(int _sell_cost) {
	this->_sell_cost = _sell_cost;
}
void Tower::setUpgradeCost(int _upgrade_cost) {
	this->_upgrade_cost = _upgrade_cost;
}

void Tower::attack() {
	cout << "Tower attacking..." << endl;
	cout << yellow << this->_name << " attacking Critter " << this->_target->getId() << "... ";
	this->_target->inflictDamage(this->getPower());
	cout << yellow << this->_target->getHitPoints() << "HP" << endl;
}

/** 
* @brief Determines collision path based on position of tower object and the distance in a straight line towards critter 
* @return std::pair<float, float>
*/
std::pair<float, float> Tower::findCollisionPath(Critter* critter) {
	return std::pair<float, float> (this->getPosition().first - critter->getPosition().first, this->getPosition().second - critter->getPosition().second);
}

/**
* @brief Calculates angle between an x and y component in degrees from the horizontal
* @return float
*/
float Tower::angleInDegrees(float x, float y) {
	return std::atan2(x, y) * 180 / M_PI;
}

/**
* @brief Rotates the tower to face the critter it is attacking
* @return void
*/
void Tower::rotateTowardsTarget() {
	std::pair<float, float> collisionPath = findCollisionPath(this->_target);

	float facingCritterAngle = angleInDegrees(collisionPath.first, collisionPath.second);

	cout << "CollisionPath ("<< collisionPath.first << ", " << collisionPath.second << ")";
	this->setRotation(facingCritterAngle);
	//this->move(this->getPosition().x + this->getSpriteSize().x/2, this->getPosition().y + this->getSpriteSize().y/2); 
}

void Tower::applySpecialEffect(Critter* critter) {
	switch(this->_special_effect) {
		/*
		case SpecialEffect::Bomb:
		cout << red << "Applying bomb" << endl;
		break;
		*/
		/*
		case SpecialEffect::Electrocute:
		cout << red << "Applying electrocute" << endl;
		break;
		*/
	case SpecialEffect::Burning: {
		cout << red << "Applying burning" << endl;
								 }
								 break;

	case SpecialEffect::Freezing: {
		//cout << red << "Applying Freezing Effect" << endl;

		//float speedBeforeFrozen = critter->getSpeed();
		//cout << "speed before frozen " << speedBeforeFrozen << endl;

		//critter->setSpeed(0.0f);
		//cout << "speed after frozen " << critter->getSpeed() << endl;

		//
		//sf::Clock frozenClock;
		//sf::Time frozenTime;

		//frozenTime = frozenClock.getElapsedTime();
		//cout << "frozen time in seconds" << frozenTime.asSeconds() << endl;
		//
		//if(frozenTime.asSeconds() < 3) {
		//	cout << "IN IF: frozen time in seconds" << frozenTime.asSeconds() << endl;
		//	frozenTime += frozenClock.getElapsedTime();
		//	frozenClock.restart();
		//}
		//critter->setSpeed(speedBeforeFrozen);
		//cout << "speed completing frozen " << critter->getSpeed() << endl;

		//cout << red << "Unfreezing" << endl;
								  }
								  break;

	case SpecialEffect::Slowing: {
		cout << red << "Applying Slowing Effect" << endl;
		cout << red << "Initial speed: " << critter->getSpeed() << endl;
		critter->reduceSpeed(10.0f);
		cout << red << "Final speed: " << critter->getSpeed() << endl;
								 }
								 break;

	case SpecialEffect::None: {
		cout << red << "Applying no effect" << endl;
							  }
							  break;
	}
}


std::string Tower::getTowerSpecs() {
	//Since we can't cout an enum in C++, we need this Array system as a workaround (optional, but prettier at output)
	char *UpgradeLevelA[] = { "Baby", "Teen", "Adult" };
	char *RateOfFireA[] = { "Slow", "Normal", "Fast" };
	char *SpecialEffectA[] = { "None", "Slowing", "Burning", "Freezing" };
	std::stringstream output;
	output << "CURRENT TOWER SPECIFICATIONS:" << std::endl;
	output << "Name: " << this->_name << std::endl;
	output << "Upgrade: " << UpgradeLevelA[this->_upgrade_level] << std::endl;
	output << "Power: " << this->_power << std::endl;
	output << "Range:  " << this->_range << std::endl;
	output << "Fire Rate: " << RateOfFireA[this->_rate_of_fire-1] << std::endl;
	output << "Buy Cost: " << this->getBuyCost() << " coins" << std::endl;
	output << "Upgrade Cost: " << this->_upgrade_cost << " coins" << std::endl;
	output << "Sell Cost: " << this->_sell_cost << " coins" << std::endl;
	output << "Strategy: " << this->_strategy->getName().c_str() << std::endl;

	return output.str();
}