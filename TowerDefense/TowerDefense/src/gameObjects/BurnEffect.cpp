#pragma once
#include <GameObjects/BurnEffect.h>

BurnEffect::BurnEffect() {}

BurnEffect::BurnEffect(Tower* tower) : _decoratedTower(tower) {
	this->load("resources/images/towers/firetower.png");
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
}

void BurnEffect::attack() {
	Tower::attack();
	cout << red << "BurnEffect on critter " << _target->getId() << endl;
	this->_target->addEffect(new Burn());
}

// @Override
std::string BurnEffect::getTowerSpecs() {
	std::stringstream output;
	output << _decoratedTower->getTowerSpecs();
	output << "Special Effect: Burning" << std::endl;
	return output.str();
}