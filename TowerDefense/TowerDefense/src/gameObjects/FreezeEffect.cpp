#pragma once
#include <GameObjects/FreezeEffect.h>

FreezeEffect::FreezeEffect() {
	std::cout << green << "FreezeEffect Default Constructor called." << std::endl;
}

FreezeEffect::FreezeEffect(Tower* decoratedTower) : _decoratedTower(decoratedTower) {
	this->load("resources/images/towers/icetower.png");
	this->setPosition(decoratedTower->getPosition().first, decoratedTower->getPosition().second);		// has to be set BEFORE setRange();

	this->_id = decoratedTower->getID();
	this->_name = "FreezeTower_" + std::to_string(this->_id);
	this->_type = decoratedTower->getType();
	this->_buy_cost = decoratedTower->getBuyCost();
	this->_power = decoratedTower->getPower();
	this->_range = decoratedTower->getRange();
	this->setRangeShape(_range);
	this->_rate_of_fire = decoratedTower->getRateOfFire();
	this->_upgrade_cost = 20;
	this->_sell_cost = 30;
	this->_special_effect = "Freezing Critter";
	this->_target = decoratedTower->getTarget();
	
	std::cout << green << this->_name << " has been created." << std::endl;
}

int FreezeEffect::getBuyCost() const {
	return _decoratedTower->getBuyCost() + 20;
}

void FreezeEffect::attack() {
		this->_target = _decoratedTower->getTarget();
		std::cout << yellow << "Target address: " << this->getTarget() << std::endl;
		std::cout << yellow << "FreezeEffect Attacking..." << std::endl;
}

// @Override
std::string FreezeEffect::getTowerSpecs() {
	std::stringstream output;
	output << _decoratedTower->getTowerSpecs() << std::endl;
	output << "Special Effect: " << this->_special_effect << std::endl;
	return output.str();
}