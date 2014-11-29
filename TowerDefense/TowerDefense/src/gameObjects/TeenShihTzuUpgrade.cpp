#pragma once
#include <GameObjects/TeenShihTzuUpgrade.h>

int TeenShihTzuUpgrade::teen_upgrade_cost = 20;

TeenShihTzuUpgrade::TeenShihTzuUpgrade() {
	std::cout << green << "TeenShihTzuUpgrade Default Constructor called." << std::endl;
}

TeenShihTzuUpgrade::TeenShihTzuUpgrade(Tower* tower) {
	this->_decoratedTower = tower;

	this->load("resources/images/towers/ShihTzu_1.png");
	this->setPosition(tower->getPosition().first, tower->getPosition().second);		// has to be set BEFORE setRange();

	this->_id = tower->getID();
	this->_name = tower->getName();
	this->_type = tower->getType();
	this->_upgrade_level = Tower::UpgradeLevel::Teen;
	this->_buy_cost = tower->getBuyCost();
	this->_power = tower->getPower() + 1;
	this->setRange(tower->getRange() + 0.5);
	this->_rate_of_fire = tower->getRateOfFire();
	this->_upgrade_cost = tower->getUpgradeCost();
	this->_sell_cost = tower->getSellCost();
	this->_strategy.reset(tower->getStrategy());

	std::cout << green << "Tower has grown up to Teen." << std::endl;
}

// @Override
std::string TeenShihTzuUpgrade::getTowerSpecs() {
	std::stringstream output;
	output << Tower::getTowerSpecs();
	return output.str();
}