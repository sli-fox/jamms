#pragma once
#include <GameObjects/SlowEffect.h>

SlowEffect::SlowEffect() {}

SlowEffect::SlowEffect(Tower* tower) {
	this->_decoratedTower = tower;

	this->load("resources/images/towers/tower.png");
	this->setPosition(tower->getPosition().first, tower->getPosition().second);		// has to be set BEFORE setRange();

	this->_id = tower->getID();
	this->_name = tower->getName();
	this->_type = tower->getType();
	this->_upgrade_level = tower->getUpgradeLevel();
	this->_buy_cost = tower->getBuyCost();
	this->_power = tower->getPower();
	this->setRange(tower->getRange());
	this->_rate_of_fire = tower->getRateOfFire();
	this->_upgrade_cost = tower->getUpgradeCost();
	this->_sell_cost = tower->getSellCost();
	this->_target = tower->getTarget();
	this->_strategy.reset(tower->getStrategy());
}

void SlowEffect::attack() {
	Tower::attack();
	cout << red << this->getName() << " is Applying Slowing Effect to Critter " << _target->getId() << endl;
	this->_target->addEffect(new Slowe());
}

// @Override
std::string SlowEffect::getTowerSpecs() {
	std::stringstream output;
	output << Tower::getTowerSpecs();
	output << "Special Effect: Slowing" << std::endl;
	return output.str();
}