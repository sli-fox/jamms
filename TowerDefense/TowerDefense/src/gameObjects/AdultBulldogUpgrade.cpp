#pragma once
#include <GameObjects/AdultBulldogUpgrade.h>

int AdultBulldogUpgrade::adult_upgrade_cost = 30;

AdultBulldogUpgrade::AdultBulldogUpgrade() {
	std::cout << green << "AdultBulldogUpgrade Default Constructor called." << std::endl;
}

AdultBulldogUpgrade::AdultBulldogUpgrade(Tower* tower) : _decoratedTower(tower) {
	tower->load("resources/images/towers/Bulldog_2.png");
	tower->setName("AdultBulldog_"+ std::to_string(tower->getID()));
	tower->setRange(tower->getRange()+0.5);
	tower->setUpgradeLevel(Tower::UpgradeLevel::Adult);
	std::cout << green << tower->getName() << " has grown up to Adult." << std::endl;
}

int AdultBulldogUpgrade::getBuyCost() const {
	return _decoratedTower->getBuyCost() + 20;
}

void AdultBulldogUpgrade::setRange(float _range) {
	this->_range = _range;
	this->setRangeShape(_range);
	_decoratedTower->setRange(_range);
}

/**
  * @brief Determines whether tower can attack a critter based on whether the critter falls within its range while taking into account the tower's rate of fire delay
  * @return bool
  */
bool AdultBulldogUpgrade::canAttack(Critter* critter) {
	return _decoratedTower->canAttack(critter);
}

void AdultBulldogUpgrade::attack() {
		this->_target = _decoratedTower->getTarget();
		_decoratedTower->attack();
		std::cout << yellow << this->_name << " attacking..." << std::endl;
}

// @Override
std::string AdultBulldogUpgrade::getTowerSpecs() {
	std::stringstream output;
	output << _decoratedTower->getTowerSpecs() << std::endl;
	return output.str();
}