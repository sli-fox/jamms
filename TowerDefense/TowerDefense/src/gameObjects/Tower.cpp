#pragma once
#include <GameObjects/Tower.h>
#define _USE_MATH_DEFINES
#include <math.h>

Tower::Tower() {
	this->_upgrade_level = Tower::UpgradeLevel::Upgrade0;
	this->_target = NULL;
	this->time = clock.getElapsedTime();
	this->_strategy.reset(new WeakestStrategy());
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
Tower::RateOfFire Tower::getRateOfFire() const {
	return _rate_of_fire;
}
Tower::SpecialEffect Tower::getSpecialEffect() const {
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
void Tower::setRange(float _range) {
	this->_range = _range;
	this->setRangeShape(_range);
}
void Tower::setRateOfFire(Tower::RateOfFire _rate_of_fire) {
	this->_rate_of_fire = _rate_of_fire;
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
void Tower::setTarget(Critter* crit) {
	this->_target = crit;
}

void Tower::setRangeShape(float range) {
	range *= 32;
	_range_shape.setPosition(this->getPosition().first, this->getPosition().second);
	_range_shape.setRadius(range);
	_range_shape.setFillColor(sf::Color::Transparent);
	_range_shape.setOutlineThickness(2);
	_range_shape.setOutlineColor(sf::Color::Red);
	_range_shape.setOrigin(range-16, range-16);
}

sf::CircleShape Tower::getRangeShape() const {
	return _range_shape;
}

/**
  * @brief Determines whether tower can attack a critter based on whether the critter falls within its range while taking into account the tower's rate of fire delay
  * @return bool
  */
bool Tower::canAttack(Critter* critter) { //@MARK canAttack() is performing 3 functions. range checking, attack timer checking, and target selection. we should split them into 3 methods in my opinion -Jeremy-
	
	if(!this->_target == NULL && (!this->circleToCircleIntersection(_target) || !_target->isActive))
		this->_target = NULL;

	if(this->_target == NULL) {
		_target = critter;
		//this->rotateTowardsTarget();
	}
	else{
		_target = executeStrategy(critter);
		//_target = critter;
		// I changed them to be more consistent -Jeremy-
	}

	this->time = this->clock.getElapsedTime();
	
	if(this->circleToCircleIntersection(_target) && time.asSeconds()*this->getRateOfFire() >= 1){
		clock.restart();
		return true;
	}

	return false;
}

Critter* Tower::attack() {
	std::cout << yellow << "WOUF WOUF! Scared cat " << this->_target->getId() << "!" << std::endl;
	this->_target->inflictDamage(this->getPower());
	std::cout << yellow << "Cat " << this->_target->getId() << " now has " << this->_target->getHitPoints() << " HP" << std::endl;
	return _target;
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

/**
  * @brief Determines whether tower can apply a special effect on a critter based on whether the critter falls within its range while taking into account the tower's rate of fire delay
  * @return bool
  */
bool Tower::canApplySpecialAfterEffects(Critter* critter) {
	this->time = this->clock.getElapsedTime();
	
	if(this->circleToCircleIntersection(critter) && time.asSeconds()*this->getRateOfFire() >= 1) {
		clock.restart();
		return true;
	}
	return false;
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
	output << "CURRENT TOWER SPECIFICATIONS:" << std::endl;
	output << "Name: " << this->_name << std::endl;
	output << "Type: " << TowerTypeA[this->_type] << std::endl;
	output << "Upgrade: " << UpgradeLevelA[this->_upgrade_level] << std::endl;
	output << "Power: " << this->_power << std::endl;
	output << "Range:  " << this->_range << std::endl;
	output << "Fire Rate: " << RateOfFireA[this->_rate_of_fire-1] << std::endl;
	if(this->_special_effect != SpecialEffect::None)
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

	std::pair <int, int> distance (this->getSpriteCenter().first - game_object->getSpriteCenter().first, this->getSpriteCenter().second - game_object->getSpriteCenter().second);  
	
	return std::sqrt(std::pow(distance.first, 2) + std::pow(distance.second, 2)) <= radius;
}

TowerStrategy* Tower::getStrategy() const{
	return this->_strategy.get();
}

void Tower::setStrategy(TowerStrategy* newStrategy){
	this->_strategy.reset(newStrategy);
}

Critter* Tower::executeStrategy(Critter* critter){
	return this->_strategy->computeTarget(critter, _target, this);
}
