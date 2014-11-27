#pragma once
#include <GameObjects/AdultShihTzuUpgrade.h>

int AdultShihTzuUpgrade::adult_upgrade_cost = 30;

AdultShihTzuUpgrade::AdultShihTzuUpgrade() {
	std::cout << green << "AdultShihTzuUpgrade Default Constructor called." << std::endl;
}

AdultShihTzuUpgrade::AdultShihTzuUpgrade(Tower* tower) : _decoratedTower(tower) {
	this->load("resources/images/towers/ShihTzu_2.png");
	this->setPosition(tower->getPosition().first, tower->getPosition().second);		// has to be set BEFORE setRange();

	this->_id = tower->getID();
	this->_name = tower->getName();
	this->_type = tower->getType();
	this->_upgrade_level = Tower::UpgradeLevel::Adult;
	this->_buy_cost = tower->getBuyCost();
	this->_power = tower->getPower() + 1;
	this->setRange(tower->getRange() + 0.5);
	this->_rate_of_fire = tower->getRateOfFire();
	this->_upgrade_cost = tower->getUpgradeCost();
	this->_sell_cost = tower->getSellCost();

	std::cout << green << "Tower has grown up to Adult." << std::endl;
}

// @Override
std::string AdultShihTzuUpgrade::getTowerSpecs() {
	std::stringstream output;
	output << Tower::getTowerSpecs() << std::endl;
	return output.str();
}