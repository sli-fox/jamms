#pragma once
#include <GameObjects/BurnEffect.h>

int BurnEffect::upgrade_cost = 25;

BurnEffect::BurnEffect() {
	std::cout << green << "BurnEffect Default Constructor called." << std::endl;
}

BurnEffect::BurnEffect(Tower* decoratedTower) : _decoratedTower(decoratedTower) {
	this->load("resources/images/towers/firetower.png");
	this->setPosition(decoratedTower->getPosition().first, decoratedTower->getPosition().second);		// has to be set BEFORE setRange();

	this->_id = decoratedTower->getID();
	this->_name = "BurnTower_" + std::to_string(this->_id);
	this->_type = decoratedTower->getType();
	this->_buy_cost = decoratedTower->getBuyCost();
	this->_power = decoratedTower->getPower();
	this->_range = decoratedTower->getRange();
	this->setRangeShape(_range);
	this->_rate_of_fire = decoratedTower->getRateOfFire();
	this->_upgrade_cost = 20;
	this->_sell_cost = 30;
	this->_special_effect = "Burning Critter";		// used for getTowerSpecs() only
	this->_target = decoratedTower->getTarget();
	
	std::cout << green << this->_name << " has been created." << std::endl;
}

int BurnEffect::getBuyCost() const {
	return _decoratedTower->getBuyCost() + 20;
}

void BurnEffect::setRange(float _range) {
	this->_range = _range;
	this->setRangeShape(_range);
	_decoratedTower->setRange(_range);
}

/**
  * @brief Determines whether tower can attack a critter based on whether the critter falls within its range while taking into account the tower's rate of fire delay
  * @return bool
  */
bool BurnEffect::canAttack(Critter* critter) {
	return _decoratedTower->canAttack(critter);
}

void BurnEffect::attack() {
		this->_target = _decoratedTower->getTarget();
		_decoratedTower->attack();
		std::cout << yellow << this->_name << " attacking..." << std::endl;
}

// @Override
std::string BurnEffect::getTowerSpecs() {
	std::stringstream output;
	output << _decoratedTower->getTowerSpecs() << std::endl;
	output << "Special Effect: " << this->_special_effect << std::endl;
	return output.str();
}