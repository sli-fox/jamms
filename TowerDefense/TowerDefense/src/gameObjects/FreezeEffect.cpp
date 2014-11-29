#pragma once
#include <GameObjects/FreezeEffect.h>

FreezeEffect::FreezeEffect() {}

FreezeEffect::FreezeEffect(Tower* tower) {
	this->_decoratedTower = tower;

	this->load("resources/images/towers/icetower.png");
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

void FreezeEffect::attack() {
	Tower::attack();
	cout << red << "FreezeEffect critter " << _target->getId() << endl;
	this->_target->addEffect(new Freeze());
}

// @Override
std::string FreezeEffect::getTowerSpecs() {
	std::stringstream output;
	output << Tower::getTowerSpecs();
	output << "Special Effect: Freezing" << std::endl;
	return output.str();
}